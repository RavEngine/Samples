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
	
	auto menu = mainMenu->AddComponent<GUIComponent>(new GUIComponent("main-menu"));
	auto doc = menu->AddDocument("mainmenu.rml");
	
	struct EventListener: public Rml::EventListener{
		void ProcessEvent(Rml::Event& event) override{
			App::Quit();
		}
	};
	doc->GetElementById("quitbtn")->AddEventListener("click", new EventListener());
	
	Spawn(mainMenu);
	
	Ref<InputManager> im = new InputManager();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
		
	im->BindAxis("MouseX", menu.get(), &GUIComponent::MouseX, CID::ANY);
	im->BindAxis("MouseY", menu.get(), &GUIComponent::MouseY, CID::ANY);
	im->BindAnyAction(menu.get());
	
	im->AddActionMap("LoadGame", SDL_SCANCODE_G);
	im->BindAction("LoadGame", this, &MainMenu::LoadGame,  ActionState::Pressed, CID::ANY);
	
	App::inputManager = im;
}

void MainMenu::LoadGame(){
	auto gui = mainMenu->GetComponent<GUIComponent>();
	gui->GetDocument("mainmenu.rml")->Hide();
	gui->AddDocument("loading.rml");
	std::thread worker([&]{
		Ref<GameWorld> g = new GameWorld();

		App::DispatchMainThread([=]{
			App::currentWorld = g;
		});
	});
	worker.detach();
}
