#include "MainMenu.hpp"
#include <RavEngine/Entity.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include "GameWorld.hpp"
#include <RavEngine/Debug.hpp>

using namespace RavEngine;

MainMenu::MainMenu(){
	Ref<Entity> mainMenu = new Entity();
	
	auto menu = mainMenu->AddComponent<GUIComponent>(new GUIComponent("main-menu"));
	menu->AddDocument("mainmenu.rml");
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
	std::thread worker([&]{
		Debug::Log("Background loading main game");
		Ref<GameWorld> g = new GameWorld();

		App::DispatchMainThread([=]{
			App::currentWorld = g;
		});
	});
	worker.detach();
}
