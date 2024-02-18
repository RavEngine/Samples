#include <RavEngine/World.hpp>
#include "GameWorld.hpp"
#include <RavEngine/InputManager.hpp>
#include "MainMenu.hpp"
#include "RavEngine/App.hpp"
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/StartApp.hpp>

using namespace RavEngine;

class AirHockey : public RavEngine::App {
    void OnStartup(int argc, char** argv) final{
        //setup video settings
        RenderEngine::VideoSettings.vsync = true;
        
        AddWorld(RavEngine::New<MainMenu>());
    }
    
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};

START_APP(AirHockey)
