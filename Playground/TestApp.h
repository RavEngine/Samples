#pragma once 

#include "WorldTest.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/WeakRef.hpp>

class TestApp : public RavEngine::App{
public:
	TestApp() : App("RavEngine_Sample_Playground"){}
private:
	void OnStartup(int argc, char** argv) override{

		//setup video settings
		RavEngine::RenderEngine::VideoSettings.vsync = true;
		RavEngine::RenderEngine::VideoSettings.width = 800;
		RavEngine::RenderEngine::VideoSettings.height = 480;

		//create a world
		auto world = std::make_shared<TestWorld>();
		world->SetupInputs();
		SetWorld(world);
		
		SetWindowTitle(fmt::format("RavEngine Playground | {}", Renderer->currentBackend()).c_str());
	}

	int OnShutdown() override {
		return 0;
	}
};
