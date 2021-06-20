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
	}

	// if client, spawn objects

	//Spawn(make_shared<NetEntity>());

	// load sync
	//systemManager.EmplaceTimedSystem<SyncNetTransforms>(std::chrono::seconds(1));
}

void RelayComp::RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin)
{
}
