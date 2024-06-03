#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/Format.hpp>
#include <RavEngine/StartApp.hpp>

using namespace std;

struct Performance_B : public RavEngine::App {
public:
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
private:
    void OnStartup(int argc, char** argv) final{

        // load world
        AddWorld(RavEngine::New<PerfB_World>());

        SetWindowTitle(RavEngine::VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }

    bool NeedsAudio() const final {
        return false;
    }
};

START_APP(Performance_B)
