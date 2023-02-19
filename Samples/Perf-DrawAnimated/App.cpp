#include "PerfC_World.hpp"
#include "RavEngine/App.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace RavEngine;
class Performance_C : public RavEngine::App{
public:
	Performance_C() : App(APPNAME){}
private:
    void OnStartup(int argc, char** argv) override{
        //setup video settings
        RenderEngine::VideoSettings.vsync = false;
        
        GetRenderEngine().SyncVideoSettings();
        
        //unlock the tickrate
        //SetMinTickTime(std::chrono::duration<double, std::milli>(0));
        
        AddWorld(RavEngine::New<PerfC_World>());
        
        SetWindowTitle(StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};


START_APP(Performance_C);
