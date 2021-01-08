#pragma once

#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>

class MainMenu : public RavEngine::World, public RavEngine::IInputListener{
public:
	MainMenu();
private:
	void LoadGame(int);
	Ref<RavEngine::Entity> mainMenu;
};
