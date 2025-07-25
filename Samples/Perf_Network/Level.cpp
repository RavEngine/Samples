#include "Level.hpp"
#include "NetEntity.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RmlUi/Core.h>

using namespace RavEngine;
using namespace std;

#if !RVE_SERVER
STATIC(NetEntity::matinst);
#endif

Level::Level() : World("level") {

#if !RVE_SERVER
	// create camera and lights
	auto camEntity = Instantiate<GameObject>();
	auto& camera = camEntity.EmplaceComponent<CameraComponent>();
	camera.SetActive(true);
	camEntity.GetTransform().LocalTranslateDelta(vector3(0, 0, 10));

	auto lightEntity = Instantiate<GameObject>();
	auto& ambientLight = lightEntity.EmplaceComponent<AmbientLight>();
	auto& dirLight = lightEntity.EmplaceComponent<DirectionalLight>();
    dirLight.SetIntensity(4);
	ambientLight.SetIntensity(0.2);
	lightEntity.GetTransform().SetLocalRotation(vector3(0, deg_to_rad(45.0), deg_to_rad(45.0)));
#endif

	// spawn the management relay if on server
	// if on client, this will be spawned automatically
	if (GetApp()->networkManager.IsServer()) {
		SetupServer();
	}
	else {
		SetupClient();
	}
}

void Level::ServerUpdateGUI()
{
#if !RVE_SERVER

	// get the GUIComponent
	auto& gui = GetComponent<GUIComponent>();
	auto doc = gui.GetDocument("server.rml");
	auto root = doc->GetElementById("root");
	root->SetInnerRML("");	//clear element
	for (const auto& con : GetApp()->networkManager.server->GetClients()) {
		auto textNode = doc->CreateElement("p");
		auto button = doc->CreateElement("button");
		button->SetInnerRML("Kick");
		textNode->SetInnerRML(Format("id = {}",con));

		struct KickEventListener : public Rml::EventListener {
			HSteamNetConnection con;
			KickEventListener(decltype(con) c) : con(c){}

			void ProcessEvent(Rml::Event& event) final {
				GetApp()->networkManager.server->DisconnectClient(con,1);
			}
		};

		button->AddEventListener(Rml::EventId::Click, new KickEventListener(con));

		textNode->AppendChild(std::move(button));
		root->AppendChild(std::move(textNode));
	}
#else
    Debug::Log("Connections:\n");
    for (const auto& con : GetApp()->networkManager.server->GetClients()) {
        Debug::Log("{}", con);
    }
#endif
}

void Level::SetupServer()
{
    
    Instantiate<ManagementRelay>();
	EmplaceSystem<TweenEntities>();
	GetApp()->networkManager.server->OnClientConnected = [&](HSteamNetConnection) {
		ServerUpdateGUI();
	};
	GetApp()->networkManager.server->OnClientDisconnected = [&](HSteamNetConnection) {
		ServerUpdateGUI();
	};
#if !RVE_SERVER
	auto guientity = Instantiate<Entity>();
	auto& guic = guientity.EmplaceComponent<GUIComponent>();
	guic.AddDocument("server.rml");

	auto im = GetApp()->inputManager = RavEngine::New<RavEngine::InputManager>();
    ComponentHandle<GUIComponent> gh(guientity);
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(gh->GetData());
#endif
}

void Level::SetupClient()
{
	GetApp()->networkManager.client->SetNetSpawnHook<ManagementRelay>([](Entity e, Ref<World> w) -> void {
		// the management relay is here, so now we want to spawn objects with their ownership transfered here
		auto& rpc = e.GetComponent<RPCComponent>();
		rpc.InvokeServerRPC(SpawnReq, NetworkBase::Reliability::Reliable, (int)0);
	});
	// only the clients move objects and need to push changes up
	// the server will automatically replicate changes from the other clients
    EmplaceTimedSystem<SyncNetTransforms>(std::chrono::milliseconds(100));
    EmplaceSystem<MoveEntities>();
    EmplaceSystem<TweenEntities>();
}

void RelayComp::RequestSpawnObject(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin)
{
	// create entities
	constexpr auto num_entities =
#ifdef _DEBUG
		2
#else
		10
#endif
		;
    auto wptr = GetOwner().GetWorld();
    Array<NetEntity, num_entities> entities;
	for (int i = 0; i < entities.size(); i++) {
		entities[i] = wptr->Instantiate<NetEntity>();
	}
    
	// transfer their ownership to the client
	for (const auto& entity : entities) {
		GetApp()->networkManager.server->ChangeOwnership(origin, ComponentHandle<NetworkIdentity>(entity));
	}
}
