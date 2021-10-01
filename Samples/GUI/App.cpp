#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

struct App : public RavEngine::App{
	App() : RavEngine::App(APPNAME){}
	void OnStartup(int argc, char** argv) override;
};

void ::App::OnStartup(int argc, char **argv){
	
	RavEngine::RenderEngine::VideoSettings.vsync = true;
	RavEngine::RenderEngine::VideoSettings.width = 800;
	RavEngine::RenderEngine::VideoSettings.height = 480;
		
	AddWorld(std::make_shared<::World>());
	
	SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
}

START_APP(::App)
