#include "Level.hpp"
#include "NetEntity.hpp"

using namespace RavEngine;
using namespace std;

STATIC(NetEntity::matinst);
STATIC(NetEntity::mesh);

void Level::OnActivate() {

	// create camera and lights
	auto camEntity = make_shared<Entity>();
	auto camera = camEntity->EmplaceComponent<CameraComponent>();
	camera->setActive(true);
	camEntity->transform()->LocalTranslateDelta(vector3(0, 0, 5));
	Spawn(camEntity);

	auto lightEntity = make_shared<Entity>();
	auto ambientLight = lightEntity->EmplaceComponent<AmbientLight>();
	auto dirLight = lightEntity->EmplaceComponent<DirectionalLight>();
	ambientLight->Intensity = 0.2;
	lightEntity->transform()->SetLocalRotation(vector3(0, glm::radians(45.0), glm::radians(45.0)));
	Spawn(lightEntity);

	// spawn the management relay if on server
	// if on client, this will be spawned automatically
	if (App::networkManager.IsServer()) {
		Spawn(make_shared<ManagementRelay>());
		systemManager.EmplaceSystem<TweenEntities>();
	}
	else {
		App::networkManager.client->SetNetSpawnHook<ManagementRelay>([](Ref<Entity> e, Ref<World> w) -> void {
			// the management relay is here, so now we want to spawn objects with their ownership transfered here
			auto rpc = e->GetComponent<RPCComponent>().value();
			rpc->InvokeServerRPC(SpawnReq, NetworkBase::Reliability::Reliable, (int)0);
		});
		// only the clients move objects and need to push changes up
		// the server will automatically replicate changes from the other clients
		systemManager.EmplaceTimedSystem<SyncNetTransforms>(std::chrono::milliseconds(100));
		systemManager.EmplaceSystem<MoveEntities>();
	}
	//Debug::Log("{}",type_name<std::array<char, 16>>());

}

void RelayComp::RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin)
{
	// create entities
	std::array<Ref<NetEntity>, 10> entities;
	for (int i = 0; i < entities.size(); i++) {
		entities[i] = make_shared<NetEntity>();
	}

	// spawn them
	auto w = getOwner().lock()->GetWorld().lock();
	for (const auto& entity : entities) {
		w->Spawn(entity);
	}

	// transfer their ownership to the client
	for (const auto& entity : entities) {
		App::networkManager.server->ChangeOwnership(origin, entity->GetComponent<NetworkIdentity>().value());
	}
}