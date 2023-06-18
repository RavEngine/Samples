//
//  main.cpp
//  RavEngine_Sample_Playground
//
//  Copyright © 2020 Ravbug.
//

#include "WorldTest.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/WeakRef.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "TestEntity.hpp"
#include "AppInfo.hpp"

class TestApp : public RavEngine::App{
	void OnStartup(int argc, char** argv) override{
		
		//setup video settings
		RavEngine::RenderEngine::VideoSettings.vsync = false;
		RavEngine::RenderEngine::VideoSettings.width = 800;
		RavEngine::RenderEngine::VideoSettings.height = 480;
		
		//create a world
		AddWorld(RavEngine::New<TestWorld>());
		
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};


START_APP(TestApp)
