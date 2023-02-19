#include <RavEngine/World.hpp>
#include "GameWorld.hpp"
#include <RavEngine/InputManager.hpp>
#include "MainMenu.hpp"
#include "RavEngine/App.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace RavEngine;

class AirHockey : public RavEngine::App {
public:
	AirHockey() : App(APPNAME){}
private:
    void OnStartup(int argc, char** argv) final{
        //setup video settings
        RenderEngine::VideoSettings.vsync = true;
        RenderEngine::VideoSettings.width = 800;
        RenderEngine::VideoSettings.height = 480;

        SetMinTickTime(std::chrono::duration<double,std::milli>(1.0/120 * 1000));
        
        AddWorld(RavEngine::New<MainMenu>());
    }
    
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};

START_APP(AirHockey)
