#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace std;

struct Performance_B : public RavEngine::App {
public:
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
private:
    void OnStartup(int argc, char** argv) final{
        //unlock tickrate
        //SetMinTickTime(std::chrono::duration<double, std::milli>(0));

        // load world
        AddWorld(RavEngine::New<PerfB_World>());

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
};

START_APP(Performance_B)
