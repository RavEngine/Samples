#include "App.hpp"
#include "PerfC_World.hpp"
#include <SDL_main.h>

using namespace RavEngine;

void Performance_C::OnStartup(int argc, char **argv){
	//setup video settings
	RenderEngine::VideoSettings.vsync = true;
	RenderEngine::VideoSettings.width = 1280;
	RenderEngine::VideoSettings.height = 720;
	
	Renderer->SyncVideoSettings();
    
    //unlock the tickrate
    SetMinTickTime(std::chrono::duration<double, std::milli>(0));
	
	AddWorld(std::make_shared<PerfC_World>());
	
	SetWindowTitle(fmt::format("RavEngine Performance_C | {}", Renderer->currentBackend()).c_str());
}

START_APP(Performance_C);
