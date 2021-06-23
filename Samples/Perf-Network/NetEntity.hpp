#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/AccessType.hpp>
#include <RavEngine/QueryIterator.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/Tween.hpp>

enum class RPCs {
	UpdateTransform,
};

struct InterpolationTransform : public RavEngine::Component, public RavEngine::Queryable<InterpolationTransform> {
	RavEngine::SpinLock mtx;
	RavEngine::Tween<decimalType, decimalType, decimalType> translate;
	RavEngine::Tween<decimalType, decimalType, decimalType, decimalType> rotate;
	bool ok = false;
};

struct NetTransform : public RavEngine::Component, public RavEngine::Queryable<NetTransform> {
	void UpdateTransform(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin) {
		auto owner = getOwner().lock();
		// update server's copy of this transform
		auto itr = owner->GetComponent<InterpolationTransform>().value();
		itr->mtx.lock();
		std::optional<RawVec3> td;
		if (td = upk.get<RawVec3>()) {
			auto currentpos = owner->transform()->GetLocalPosition();
			RavEngine::Debug::Assert(!std::isnan(currentpos.x),"CurrentPos was NaN!");
			RavEngine::Debug::Assert(!std::isnan(td.value()[0]),"NetworkPos was NaN!");
			// create the tween
			// another system will tick this tween
			itr->translate = decltype(itr->translate)([=](decimalType x, decimalType y, decimalType z) {
				if (isnan(x) || isnan(y) || isnan(z)) {		//sometimes the value is NaN???
					return;
				}
				owner->transform()->SetLocalPosition(vector3(x,y,z));
			},currentpos.x,currentpos.y,currentpos.z);
			auto t = td.value();
			itr->translate.AddKeyframe(0.1, RavEngine::TweenCurves::LinearCurve, t[0], t[1], t[2]);
		}
		std::optional<RawQuat> qd;
		if (qd = upk.get<RawQuat>()) {
			auto currentRot = owner->transform()->GetLocalRotation();

			itr->rotate = decltype(itr->rotate)([=](decimalType w, decimalType x, decimalType y, decimalType z) {
				if (isnan(w) || isnan(x) || isnan(y) || isnan(z)) {
					return;
				}
				owner->transform()->SetLocalRotation(quaternion(w,x,y,z));
			}, currentRot.w, currentRot.x, currentRot.y, currentRot.z);
			auto r = qd.value();
			itr->rotate.AddKeyframe(0.1, RavEngine::TweenCurves::LinearCurve, r[0],r[1],r[2],r[3]);
		}
		itr->ok = true;
		itr->mtx.unlock();

		// now RPC all the clients except the sender of this message to update their copy of this object
		// as well
		auto rpc = owner->GetComponent<RavEngine::RPCComponent>().value();
		rpc->InvokeClientRPCToAllExcept(RavEngine::to_underlying(RPCs::UpdateTransform), origin, RavEngine::NetworkBase::Reliability::Unreliable, td.value(), qd.value());
	}
};

struct PathData : public RavEngine::Component, public RavEngine::Queryable<PathData> {
	float xtiming = 0.2, ytiming = 0.5, ztiming = 0.01;
	float offset = RavEngine::Random::get(-5,5);
	float scale = 4;
};

struct SyncNetTransforms : public RavEngine::AutoCTTI {
	inline void Tick(float scale, RavEngine::AccessRead<NetTransform>, RavEngine::AccessRead<RavEngine::Transform> tr, RavEngine::AccessReadWrite<RavEngine::RPCComponent> r) {
		auto transform = tr.get();
		auto rpc = r.get();

		rpc->InvokeServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), RavEngine::NetworkBase::Reliability::Unreliable, vec3toRaw(transform->GetWorldPosition()), quatToRaw(transform->GetWorldRotation()));
	}

	inline constexpr auto QueryTypes() const {
		return RavEngine::QueryIteratorAND<NetTransform, RavEngine::Transform, RavEngine::RPCComponent>();
	}
};

struct MoveEntities : public RavEngine::AutoCTTI {
	inline void Tick(float fpsScale, RavEngine::AccessRead<PathData> pd, RavEngine::AccessReadWrite<RavEngine::Transform> tr, RavEngine::AccessRead<RavEngine::NetworkIdentity> ni) {

		// use the sine of global time
		auto netid = ni.get();
		if (netid->IsOwner()) {
			auto transform = tr.get();
			auto pathdata = pd.get();

			auto t = RavEngine::App::currentTime();

			auto pos = vector3(
				std::sin(t * pathdata->xtiming + pathdata->offset) * pathdata->scale,
				std::sin(t * pathdata->ytiming + pathdata->offset) * pathdata->scale,
				std::sin(t * pathdata->ztiming + pathdata->offset) * pathdata->scale
			);
			transform->SetWorldPosition(pos);
			auto rot = quaternion(pos);
			transform->SetLocalRotation(rot);
		}
	}

	inline constexpr auto QueryTypes() const {
		return RavEngine::QueryIteratorAND <PathData, RavEngine::Transform, RavEngine::NetworkIdentity>();
	}
};


struct TweenEntities : public RavEngine::AutoCTTI {

	inline constexpr auto QueryTypes() const {
		return RavEngine::QueryIteratorAND<InterpolationTransform>();
	}

	inline void Tick(float fpsScale, RavEngine::AccessReadWrite<InterpolationTransform> it) {
		auto itr = it.get();
		if (itr->ok) {
			itr->mtx.lock();
			itr->translate.step(fpsScale);
			itr->rotate.step(fpsScale);
			itr->mtx.unlock();
		}
	}
};

struct NetEntity : public RavEngine::Entity, public RavEngine::NetworkReplicable {

	static Ref<RavEngine::PBRMaterialInstance> matinst;
	static Ref<RavEngine::MeshAsset> mesh;

	inline void CommonInit() {
		auto rpc = EmplaceComponent<RavEngine::RPCComponent>();
		auto rpccomp = EmplaceComponent<NetTransform>();
		rpc->RegisterServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), rpccomp, &NetTransform::UpdateTransform);
		rpc->RegisterClientRPC(RavEngine::to_underlying(RPCs::UpdateTransform), rpccomp, &NetTransform::UpdateTransform);

		if (!matinst) {
			matinst = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
		}
		if (!mesh) {
			mesh = std::make_shared<RavEngine::MeshAsset>("cube.obj");
		}

		EmplaceComponent<RavEngine::StaticMesh>(mesh, matinst);
		EmplaceComponent<InterpolationTransform>();
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
		EmplaceComponent<PathData>();		// since clients control their objects, the server does not need to allocate this
	}

	RavEngine::ctti_t NetTypeID() const override {
		return RavEngine::CTTI<NetEntity>();
	}
};