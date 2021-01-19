#pragma once

#include <RavEngine/World.hpp>
#include <RavEngine/IInputListener.hpp>

class MainMenu : public RavEngine::World, public RavEngine::IInputListener{
public:
	void OnActivate() override;
private:
	void LoadGame(int);
	Ref<RavEngine::Entity> mainMenu;
};
