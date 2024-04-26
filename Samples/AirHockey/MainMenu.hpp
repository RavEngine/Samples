#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>
#include <RavEngine/SharedObject.hpp>

class MainMenu : public RavEngine::World, public RavEngine::IInputListener{
public:
	MainMenu();
private:
	void LoadGame(int);
	RavEngine::Entity mainMenu;
};
