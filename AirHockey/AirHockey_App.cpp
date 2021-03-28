#include "AirHockey_App.hpp"
#include <RavEngine/World.hpp>
#include "GameWorld.hpp"
#include <RavEngine/InputManager.hpp>
#include "MainMenu.hpp"
#include <SDL_main.h>

using namespace RavEngine;

void AirHockey::OnStartup(int argc, char** argv)
{
	//setup video settings
	RenderEngine::VideoSettings.vsync = true;
	RenderEngine::VideoSettings.width = 800;
	RenderEngine::VideoSettings.height = 480;

    SetMinTickTime(std::chrono::duration<double,std::milli>(1.0/120 * 1000));
    
	AddWorld(std::make_shared<MainMenu>());
}

int AirHockey::OnShutdown()
{
	return 0;
}

START_APP(AirHockey)
