//
//  main.cpp
//  RavEngine_Sample_Playground
//
//  Copyright © 2020 Ravbug.
//

#include "WorldTest.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/WeakRef.hpp>
#include "TestEntity.hpp"
#include "AppInfo.hpp"

class TestApp : public RavEngine::App{
public:
	TestApp() : App(APPNAME){}
private:
	void OnStartup(int argc, char** argv) override{
		
		//setup video settings
		RavEngine::RenderEngine::VideoSettings.vsync = false;
		RavEngine::RenderEngine::VideoSettings.width = 800;
		RavEngine::RenderEngine::VideoSettings.height = 480;
		
		//create a world
		AddWorld(RavEngine::New<TestWorld>());
		
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	
	int OnShutdown() override {
		return 0;
	}
};


START_APP(TestApp)
