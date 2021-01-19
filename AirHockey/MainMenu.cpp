#include "MainMenu.hpp"
#include <RavEngine/Entity.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include "GameWorld.hpp"
#include <RavEngine/Debug.hpp>

using namespace RavEngine;
using namespace std;

void MainMenu::OnActivate(){
	mainMenu = make_shared<Entity>();
	
	auto menu = mainMenu->EmplaceComponent<GUIComponent>();
	auto doc = menu->AddDocument("mainmenu.rml");
	menu->AddDocument("loading.rml")->Hide();
	
	// shown here is an example of how to bind separate event listeners
	// You can also share event listeners by reading data from the event object
	struct QuitEventListener: public Rml::EventListener{
		void ProcessEvent(Rml::Event& event) override{
			App::Quit();
		}
	};
	struct StartEventListener: public Rml::EventListener{
		WeakRef<MainMenu> menu;
		StartEventListener(const WeakRef<MainMenu>& m) : menu(m) {};
		void ProcessEvent(Rml::Event& event) override{
			menu.lock()->LoadGame(1);
		}
	};
	struct StartMultiplayerEventListener : public Rml::EventListener{
		WeakRef<MainMenu> menu;
		StartMultiplayerEventListener(const WeakRef<MainMenu>& m) : menu(m) {};
		void ProcessEvent(Rml::Event& event) override{
			menu.lock()->LoadGame(2);
		}
	};
	struct StartZeroplayerEventListener : public Rml::EventListener{
		WeakRef<MainMenu> menu;
		StartZeroplayerEventListener(const WeakRef<MainMenu>& m) : menu(m) {};
		void ProcessEvent(Rml::Event& event) override{
			menu.lock()->LoadGame(0);
		}
	};
	
	auto ptr = shared_from_this();
	
	doc->GetElementById("quitbtn")->AddEventListener("click", new QuitEventListener());
	doc->GetElementById("playsingle")->AddEventListener("click", new StartEventListener(static_pointer_cast<MainMenu>(ptr)));
	doc->GetElementById("playmulti")->AddEventListener("click", new StartMultiplayerEventListener(static_pointer_cast<MainMenu>(ptr)));
	doc->GetElementById("playzero")->AddEventListener("click", new StartZeroplayerEventListener(static_pointer_cast<MainMenu>(ptr)));
	
	
	Spawn(mainMenu);
	
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
	im->BindAxis("MouseX", menu, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", menu, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(menu);
	
	App::inputManager = im;
	
	menu->Debug();
}

void MainMenu::LoadGame(int numplayers){
	auto gui = mainMenu->GetComponent<GUIComponent>();
	gui->GetDocument("mainmenu.rml")->Hide();
	gui->GetDocument("loading.rml")->Show();
	
	std::thread worker([=]{
		Ref<GameWorld> g = make_shared<GameWorld>(numplayers);

		App::DispatchMainThread([=]{
			App::SetWorld(g);
		});
	});
	worker.detach();
}
