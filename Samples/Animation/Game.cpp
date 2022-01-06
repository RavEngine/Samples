#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>

class Game : public RavEngine::App{
public:
    Game() : RavEngine::App(APPNAME){}
    void OnStartup(int argc, char** argv) final{
        AddWorld(RavEngine::New<Level>());
            
            SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};

START_APP(Game)
