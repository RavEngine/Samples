#include "ClientMenuLevel.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/Filesystem.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include "Level.hpp"

using namespace RavEngine;
using namespace std;

void ClientMenu::OnActivate()
{
	// load the menu for joining a server
	auto guientity = Instantiate<GameObject>();
	auto& guic = guientity.EmplaceComponent<RavEngine::GUIComponent>();
    guientity.EmplaceComponent<CameraComponent>().SetActive(true);
	auto doc = guic.AddDocument("client.rml");

	// input manager to make GUI interactive
	auto im = GetApp()->inputManager = RavEngine::New<RavEngine::InputManager>();
    ComponentHandle<GUIComponent> gh(guientity);
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(guic.GetData());

	// connect event listeners
	struct ConnectEventListener : public Rml::EventListener {
		ClientMenu* world;
		Rml::ElementDocument* doc;
		ConnectEventListener(decltype(world) w, decltype(doc) d) : world(w), doc(d) {}

		void ProcessEvent(Rml::Event& event) final {
			auto field = static_cast<Rml::ElementFormControlInput*>(doc->GetElementById("addressfield"));
			auto value = field->GetValue();
            auto portfield = static_cast<Rml::ElementFormControlInput*>(doc->GetElementById("portfield"));
            auto port = std::stoi(portfield->GetValue());
			world->ConnectToServer(value,port);
		}

	};
	doc->GetElementById("gobtn")->AddEventListener(Rml::EventId::Click, new ConnectEventListener(this,doc));
}

void ClientMenu::ConnectToServer(const std::string& addr, uint16_t port) {
	auto& cl = GetApp()->networkManager.client;
	cl->Connect(addr,port);
		cl->OnConnected = [&](HSteamNetConnection) {
			Debug::Log("Client successfully connected");
			GetApp()->inputManager.reset();
			GetApp()->AddReplaceWorld(this->shared_from_this(), RavEngine::New<Level>());
		};
		cl->OnLostConnection = [&](HSteamNetConnection) {
            Dialog::ShowBasic("Information", "Disconnected", Dialog::MessageBoxType::Info);
			GetApp()->Quit();
		};
}
