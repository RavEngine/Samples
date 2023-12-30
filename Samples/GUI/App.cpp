#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>

struct App : public RavEngine::App{
    void OnStartup(int argc, char** argv) final{
        RavEngine::RenderEngine::VideoSettings.vsync = true;
                
            AddWorld(RavEngine::New<::World>());
            
            SetWindowTitle(std::format("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};

START_APP(::App)
