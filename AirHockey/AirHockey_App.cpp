#include "AirHockey_App.hpp"
#include <RavEngine/World.hpp>
#include <RavEngine/GameplayStatics.hpp>
#include "GameWorld.hpp"

using namespace RavEngine;

void AirHockey::OnStartup(int argc, char** argv)
{
	//setup video settings
	RenderEngine::VideoSettings.vsync = true;
	RenderEngine::VideoSettings.width = 800;
	RenderEngine::VideoSettings.height = 480;

	GameplayStatics::currentWorld = new GameWorld();
	GameplayStatics::inputManager = new InputManager();
}

int AirHockey::OnShutdown()
{
	return 0;
}

START_APP(AirHockey)
