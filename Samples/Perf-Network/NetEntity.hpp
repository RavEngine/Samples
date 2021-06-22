#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/AccessType.hpp>
#include <RavEngine/QueryIterator.hpp>
#include <RavEngine/StaticMesh.hpp>

enum class RPCs {
	UpdateTransform
};

struct NetTransform : public RavEngine::Component, public RavEngine::Queryable<NetTransform> {
	void UpdateTransform(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin) {
		auto owner = getOwner().lock();
		if (auto td = upk.get<RawVec3>()) {
			owner->transform()->SetWorldPosition(RawToVec3(td.value()));
		}

		if (auto qd = upk.get<RawQuat>()) {
			owner->transform()->SetWorldRotation(RawToQuat(qd.value()));
		}
	}
};

struct SyncNetTransforms : public RavEngine::AutoCTTI {
	inline void Tick(float scale,RavEngine::AccessRead<RavEngine::Transform> tr, RavEngine::AccessReadWrite<RavEngine::RPCComponent> r, RavEngine::AccessRead<NetTransform>) {
		auto transform = tr.get();
		auto rpc = r.get();

		rpc->InvokeServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), RavEngine::NetworkBase::Reliability::Reliable, vec3toRaw(transform->GetWorldPosition()), quatToRaw(transform->GetWorldRotation()));
	}

	inline constexpr RavEngine::QueryIteratorAND<RavEngine::Transform, RavEngine::RPCComponent, NetTransform> QueryTypes() const {
		return RavEngine::QueryIteratorAND<RavEngine::Transform, RavEngine::RPCComponent, NetTransform>();
	}
};

struct NetEntity : public RavEngine::Entity, public RavEngine::NetworkReplicable {

	static Ref<RavEngine::PBRMaterialInstance> matinst;
	static Ref<RavEngine::MeshAsset> mesh;

	inline void CommonInit() {
		auto rpc = EmplaceComponent<RavEngine::RPCComponent>();
		auto rpccomp = EmplaceComponent<NetTransform>();
		rpc->RegisterServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), rpccomp, &NetTransform::UpdateTransform);

		if (!matinst) {
			matinst = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
		}
		if (!mesh) {
			mesh = std::make_shared<RavEngine::MeshAsset>("cube.obj");
		}

		EmplaceComponent<RavEngine::StaticMesh>(mesh, matinst);
	}

	// server constructor
	NetEntity() {
		CommonInit();
		EmplaceComponent<RavEngine::NetworkIdentity>();
	}

	// invoked when spawned over the network
	NetEntity(const uuids::uuid& id) {
		CommonInit();
		EmplaceComponent<RavEngine::NetworkIdentity>(id);
	}

	RavEngine::ctti_t NetTypeID() const override {
		return RavEngine::CTTI<NetEntity>();
	}
};