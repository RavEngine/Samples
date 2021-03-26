#include "App.hpp"
#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
#include <SDL_main.h>

void ::App::OnStartup(int argc, char **argv){
	
	RavEngine::RenderEngine::VideoSettings.vsync = true;
	RavEngine::RenderEngine::VideoSettings.width = 800;
	RavEngine::RenderEngine::VideoSettings.height = 480;
		
	AddWorld(std::make_shared<::World>());
	
	SetWindowTitle(fmt::format("RavEngine GUIKitchenSink | {}", Renderer->currentBackend()).c_str());
}

START_APP(::App)
