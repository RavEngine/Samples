#include <RavEngine/App.hpp>
#include "Level.hpp"
#include "AppInfo.hpp"

struct App : public RavEngine::App{
	App() : RavEngine::App(APPNAME){}
	void OnStartup(int argc, char** argv) override{
		AddWorld(RavEngine::New<Level>());
		
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
};

START_APP(App)
