#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/NetworkReplicable.hpp>

struct Level : public RavEngine::World {
	Level() {
		auto name = "level";
		std::memcpy((char*)worldID.data(), name, sizeof(name));
	}
	void OnActivate() final;
};

struct RelayComp : public RavEngine::Component, public RavEngine::Queryable<RelayComp> {
	void RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin);
};

enum ManagerRPCs {
	SpawnReq,
	UpdateReq
};

struct ManagementRelay : public RavEngine::Entity, public RavEngine::NetworkReplicable {
	inline void CommonInit() {
		auto rpc = EmplaceComponent<RavEngine::RPCComponent>();
		auto relay = EmplaceComponent<RelayComp>();
		rpc->RegisterServerRPC(SpawnReq, relay, &RelayComp::RequestSpawnObject, RavEngine::RPCComponent::Directionality::Bidirectional);
	}

	ManagementRelay() {
		CommonInit();

		EmplaceComponent<RavEngine::NetworkIdentity>();
	}

	ManagementRelay(const uuids::uuid& id) {
		CommonInit();
		EmplaceComponent<RavEngine::NetworkIdentity>(id);
	}

	RavEngine::ctti_t NetTypeID() const override {
		return RavEngine::CTTI<ManagementRelay>();
	}
};