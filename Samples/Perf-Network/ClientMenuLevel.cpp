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
	auto guientity = std::make_shared<RavEngine::Entity>();
	auto guic = guientity->EmplaceComponent<RavEngine::GUIComponent>();
	auto doc = guic->AddDocument("client.rml");

	// input manager to make GUI interactive
	auto im = App::inputManager = std::make_shared<RavEngine::InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", guic, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", guic, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(guic);

	// connect event listeners
	struct ConnectEventListener : public Rml::EventListener {
		WeakRef<ClientMenu> world;
		Rml::ElementDocument* doc;
		ConnectEventListener(Ref<World> w, decltype(doc) d) : world(static_pointer_cast<ClientMenu>(w)), doc(d) {}

		void ProcessEvent(Rml::Event& event) final {
			auto field = static_cast<Rml::ElementFormControlInput*>(doc->GetElementById("addressfield"));
			auto value = field->GetValue();
			world.lock()->ConnectToServer(value);
		}

	};
	doc->GetElementById("gobtn")->AddEventListener(Rml::EventId::Click, new ConnectEventListener(shared_from_this(),doc));

	Spawn(guientity);
}

void ClientMenu::ConnectToServer(const std::string& addr) {
	auto& cl = App::networkManager.client;
	cl->Connect(addr,PORT);
		cl->OnConnected = [&](HSteamNetConnection) {
			Debug::Log("Client successfully connected");
			App::RemoveAllWorlds();
			App::AddWorld(make_shared<Level>());
		};
		cl->OnLostConnection = [&](HSteamNetConnection) {
			Debug::Log("Client disconnected");
			App::Quit();
		};
}
