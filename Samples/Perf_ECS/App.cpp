#include <RavEngine/App.hpp>
#include "Level.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/StartApp.hpp>

using namespace std;
using namespace RavEngine;
struct Performance_A : public RavEngine::App {
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
private:
    void OnStartup(int argc, char** argv) final{            
            GetRenderEngine().VideoSettings.vsync = false;
            GetRenderEngine().SyncVideoSettings();

            // load world
            AddWorld(RavEngine::New<PerfA_World>());

            SetWindowTitle(VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    bool NeedsAudio() const final {
        return false;
    }
};

START_APP(Performance_A)
