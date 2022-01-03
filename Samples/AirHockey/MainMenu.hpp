#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>

class MainMenu : public RavEngine::World, public RavEngine::IInputListener, public RavEngine::virtual_enable_shared_from_this<MainMenu>{
public:
	MainMenu();
private:
	void LoadGame(int);
	RavEngine::Entity mainMenu;
};
