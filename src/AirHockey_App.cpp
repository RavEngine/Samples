#include "AirHockey_App.hpp"
#include <RavEngine/World.hpp>
#include <RavEngine/GameplayStatics.hpp>
#include "GameWorld.hpp"

using namespace RavEngine;

void AirHockey::OnStartup(int argc, char** argv)
{
	//setup video settings
	GameplayStatics::VideoSettings.vsync = true;
	GameplayStatics::VideoSettings.width = 800;
	GameplayStatics::VideoSettings.height = 480;

	GameplayStatics::currentWorld = new GameWorld();
}

int AirHockey::OnShutdown()
{
	return 0;
}

START_APP(AirHockey)
