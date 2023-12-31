#include "PerfC_World.hpp"
#include "RavEngine/App.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace RavEngine;
class Performance_C : public RavEngine::App{
    void OnStartup(int argc, char** argv) override{
        //setup video settings
        RenderEngine::VideoSettings.vsync = false;
        
        GetRenderEngine().SyncVideoSettings();
        
        AddWorld(RavEngine::New<PerfC_World>());
        
        SetWindowTitle(VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};


START_APP(Performance_C);
