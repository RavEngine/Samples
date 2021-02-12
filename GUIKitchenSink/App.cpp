#include "App.hpp"
#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>

void ::App::OnStartup(int argc, char **argv){
	
	RavEngine::RenderEngine::VideoSettings.vsync = true;
	RavEngine::RenderEngine::VideoSettings.width = 800;
	RavEngine::RenderEngine::VideoSettings.height = 480;
		
	SetWorld(std::make_shared<::World>());
}

START_APP(::App)
