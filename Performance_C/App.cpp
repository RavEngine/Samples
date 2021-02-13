#include "App.hpp"
#include "PerfC_World.hpp"

using namespace RavEngine;

void Performance_C::OnStartup(int argc, char **argv){
	//setup video settings
	RenderEngine::VideoSettings.vsync = true;
	RenderEngine::VideoSettings.width = 1280;
	RenderEngine::VideoSettings.height = 720;
	
	Renderer->SyncVideoSettings();
    
    //unlock the tickrate
    SetMinTickTime(std::chrono::duration<double, std::milli>(0));
	
	SetWorld(std::make_shared<PerfC_World>());
	
	SetWindowTitle(fmt::format("RavEngine Performance_C | {}", Renderer->currentBackend()).c_str());
}

START_APP(Performance_C);
