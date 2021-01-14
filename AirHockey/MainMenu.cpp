#include "MainMenu.hpp"
#include <RavEngine/Entity.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include "GameWorld.hpp"
#include <RavEngine/Debug.hpp>

using namespace RavEngine;

MainMenu::MainMenu(){
	mainMenu = new Entity();
	
	auto menu = mainMenu->AddComponent<GUIComponent>(new GUIComponent());
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
			if (menu){
				menu.get()->LoadGame(1);
			}
		}
	};
	struct StartMultiplayerEventListener : public Rml::EventListener{
		WeakRef<MainMenu> menu;
		StartMultiplayerEventListener(const WeakRef<MainMenu>& m) : menu(m) {};
		void ProcessEvent(Rml::Event& event) override{
			if (menu){
				menu.get()->LoadGame(2);
			}
		}
	};
	struct StartZeroplayerEventListener : public Rml::EventListener{
		WeakRef<MainMenu> menu;
		StartZeroplayerEventListener(const WeakRef<MainMenu>& m) : menu(m) {};
		void ProcessEvent(Rml::Event& event) override{
			if (menu){
				menu.get()->LoadGame(0);
			}
		}
	};
	
	doc->GetElementById("quitbtn")->AddEventListener("click", new QuitEventListener());
	doc->GetElementById("playsingle")->AddEventListener("click", new StartEventListener(this));
	doc->GetElementById("playmulti")->AddEventListener("click", new StartMultiplayerEventListener(this));
	doc->GetElementById("playzero")->AddEventListener("click", new StartZeroplayerEventListener(this));
	
	
	Spawn(mainMenu);
	
	Ref<InputManager> im = new InputManager();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
		
	im->BindAxis("MouseX", menu.get(), &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", menu.get(), &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction<GUIComponent>(menu.get());
		
	App::inputManager = im;
	
	menu->Debug();
}

void MainMenu::LoadGame(int numplayers){
	auto gui = mainMenu->GetComponent<GUIComponent>();
	gui->GetDocument("mainmenu.rml")->Hide();
	gui->GetDocument("loading.rml")->Show();
	
	std::thread worker([=]{
		Ref<GameWorld> g = new GameWorld(numplayers);

		App::DispatchMainThread([=]{
			App::currentWorld = g;
		});
	});
	worker.detach();
}
