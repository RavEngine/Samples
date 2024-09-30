#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/ComponentHandle.hpp>

struct Level : public RavEngine::World {
	Level();

private:
	void ServerUpdateGUI();
	void SetupServer();
	void SetupClient();
};

struct RelayComp : public RavEngine::ComponentWithOwner, public RavEngine::Queryable<RelayComp> {
	void RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin);
    RelayComp(RavEngine::Entity owner) : ComponentWithOwner(owner){}
};

enum ManagerRPCs {
	SpawnReq,
	UpdateReq
};

struct ManagementRelay : public RavEngine::Entity {
	inline void Create() {
		auto& rpc = EmplaceComponent<RavEngine::RPCComponent>();
		EmplaceComponent<RelayComp>();
        RavEngine::ComponentHandle<RelayComp> relay(this);
        rpc.RegisterServerRPC(SpawnReq, [relay](auto& a, auto b) mutable{
            relay->RequestSpawnObject(a,b);
        }, RavEngine::RPCComponent::Directionality::Bidirectional);
	}
};
