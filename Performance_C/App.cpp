#include "App.hpp"
#include "PerfC_World.hpp"

using namespace RavEngine;

void Performance_C::OnStartup(int argc, char **argv){
	//setup video settings
	RenderEngine::VideoSettings.vsync = true;
	RenderEngine::VideoSettings.width = 800;
	RenderEngine::VideoSettings.height = 480;
	
	currentWorld = new PerfC_World();
}

START_APP(Performance_C);
