#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/App.hpp>

struct App : public RavEngine::App{
	App() : RavEngine::App("RavEngine_Sample_GUIKitchenSink"){}
	void OnStartup(int argc, char** argv) override;
};

void ::App::OnStartup(int argc, char **argv){
	
	RavEngine::RenderEngine::VideoSettings.vsync = true;
	RavEngine::RenderEngine::VideoSettings.width = 800;
	RavEngine::RenderEngine::VideoSettings.height = 480;
		
	AddWorld(std::make_shared<::World>());
	
	SetWindowTitle(RavEngine::StrFormat("RavEngine GUIKitchenSink | {}", Renderer->currentBackend()).c_str());
}

START_APP(::App)
