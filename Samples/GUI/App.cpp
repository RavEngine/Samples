#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>

struct App : public RavEngine::App{
	App() : RavEngine::App(APPNAME){}
    void OnStartup(int argc, char** argv) final{
        RavEngine::RenderEngine::VideoSettings.vsync = true;
            RavEngine::RenderEngine::VideoSettings.width = 800;
            RavEngine::RenderEngine::VideoSettings.height = 480;
                
            AddWorld(RavEngine::New<::World>());
            
            SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};

START_APP(::App)
