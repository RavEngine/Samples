#pragma once

#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>

class MainMenu : public RavEngine::World, public RavEngine::IInputListener{
public:
	MainMenu();
private:
	void LoadGame(bool);
	Ref<RavEngine::Entity> mainMenu;
};
