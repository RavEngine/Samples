#include "Level.hpp"
#include "NetEntity.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>

using namespace RavEngine;
using namespace std;

STATIC(NetEntity::matinst);
STATIC(NetEntity::mesh);

void Level::OnActivate() {

	// create camera and lights
	auto camEntity = make_shared<Entity>();
	auto camera = camEntity->EmplaceComponent<CameraComponent>();
	camera->SetActive(true);
	camEntity->transform()->LocalTranslateDelta(vector3(0, 0, 10));
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
		SetupServer();
	}
	else {
		SetupClient();
	}
	//Debug::Log("{}",type_name<std::array<char, 16>>());

}

void Level::ServerUpdateGUI()
{
	// get the GUIComponent
	auto gui = GetComponent<GUIComponent>().value();
	auto doc = gui->GetDocument("server.rml");
	auto root = doc->GetElementById("root");
	root->SetInnerRML("");	//clear element
	for (const auto& con : App::networkManager.server->GetClients()) {
		auto textNode = doc->CreateElement("p");
		auto button = doc->CreateElement("button");
		button->SetInnerRML("Kick");
		textNode->SetInnerRML(StrFormat("id = {}",con));

		struct KickEventListener : public Rml::EventListener {
			HSteamNetConnection con;
			KickEventListener(decltype(con) c) : con(c){}

			void ProcessEvent(Rml::Event& event) final {
				App::networkManager.server->DisconnectClient(con,1);
			}
		};

		button->AddEventListener("click", new KickEventListener(con));

		textNode->AppendChild(std::move(button));
		root->AppendChild(std::move(textNode));
	}
}

void Level::SetupServer()
{
	Spawn(make_shared<ManagementRelay>());
	systemManager.EmplaceSystem<TweenEntities>();
	App::networkManager.server->OnClientConnected = [&](HSteamNetConnection) {
		ServerUpdateGUI();
	};
	App::networkManager.server->OnClientDisconnected = [&](HSteamNetConnection) {
		ServerUpdateGUI();
	};

	auto guientity = make_shared<Entity>();
	auto guic = guientity->EmplaceComponent<GUIComponent>();
	guic->AddDocument("server.rml");

	auto im = App::inputManager = std::make_shared<RavEngine::InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", guic, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", guic, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(guic);

	Spawn(guientity);
}

void Level::SetupClient()
{
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

void RelayComp::RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin)
{
	// create entities
	constexpr auto num_entities =
#ifdef _DEBUG
		20
#else
		500
#endif
		;

	std::array<Ref<NetEntity>, num_entities> entities;
	for (int i = 0; i < entities.size(); i++) {
		entities[i] = make_shared<NetEntity>();
	}

	// spawn them
	auto w = GetOwner().lock()->GetWorld().lock();
	for (const auto& entity : entities) {
		w->Spawn(entity);
	}

	// transfer their ownership to the client
	for (const auto& entity : entities) {
		App::networkManager.server->ChangeOwnership(origin, entity->GetComponent<NetworkIdentity>().value());
	}
}
