#include <RavEngine/App.hpp>
#include "Level.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

struct App : public RavEngine::App{
	void OnStartup(int argc, char** argv) override{
		AddWorld(RavEngine::New<Level>());
        App::GetRenderEngine().VideoSettings.vsync = false;
        App::GetRenderEngine().SyncVideoSettings();
		
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};

START_APP(App)
