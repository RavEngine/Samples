#include <RavEngine/World.hpp>
#include "GameWorld.hpp"
#include <RavEngine/InputManager.hpp>
#include "MainMenu.hpp"
#include "RavEngine/App.hpp"

using namespace RavEngine;

class AirHockey : public RavEngine::App {
public:
	AirHockey() : App("RavEngine_Sample_AirHockey"){}
private:
	void OnStartup(int argc, char** argv) override;
	int OnShutdown() override;
};


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
