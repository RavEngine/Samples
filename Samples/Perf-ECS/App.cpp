#include <RavEngine/App.hpp>
#include "Level.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>

using namespace std;
using namespace RavEngine;
struct Performance_A : public RavEngine::App {
public:
	Performance_A() : App(APPNAME) {}
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
private:
    void OnStartup(int argc, char** argv) final{
        //unlock tickrate
            SetMinTickTime(std::chrono::duration<double, std::milli>(0));
            
            GetRenderEngine().VideoSettings.vsync = false;
            GetRenderEngine().SyncVideoSettings();

            // load world
            AddWorld(RavEngine::New<PerfA_World>());

            SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
};

START_APP(Performance_A)
