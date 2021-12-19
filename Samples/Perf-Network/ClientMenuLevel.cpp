#include "ClientMenuLevel.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include "Level.hpp"

using namespace RavEngine;
using namespace std;

void ClientMenu::OnActivate()
{
	// load the menu for joining a server
	auto guientity = CreatePrototype<Entity>();
	auto& guic = guientity.EmplaceComponent<RavEngine::GUIComponent>();
	auto doc = guic.AddDocument("client.rml");

	// input manager to make GUI interactive
	auto im = GetApp()->inputManager = std::make_shared<RavEngine::InputManager>();
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
			world->ConnectToServer(value);
		}

	};
	doc->GetElementById("gobtn")->AddEventListener(Rml::EventId::Click, new ConnectEventListener(this,doc));
}

void ClientMenu::ConnectToServer(const std::string& addr) {
	auto& cl = GetApp()->networkManager.client;
	cl->Connect(addr,PORT);
		cl->OnConnected = [&](HSteamNetConnection) {
			Debug::Log("Client successfully connected");
			GetApp()->inputManager.reset();
			GetApp()->AddReplaceWorld(this->shared_from_this(), make_shared<Level>());
		};
		cl->OnLostConnection = [&](HSteamNetConnection) {
			Debug::Log("Client disconnected");
			GetApp()->Quit();
		};
}
