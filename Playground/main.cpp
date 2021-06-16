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

class TestApp : public RavEngine::App{
public:
	TestApp() : App("RavEngine_Sample_Playground"){}
private:
	void OnStartup(int argc, char** argv) override{
		
		//setup video settings
		RavEngine::RenderEngine::VideoSettings.vsync = false;
		RavEngine::RenderEngine::VideoSettings.width = 800;
		RavEngine::RenderEngine::VideoSettings.height = 480;
		
		App::networkManager.server = std::make_unique<RavEngine::NetworkServer>();
		App::networkManager.server->Start(6969);
		
		App::networkManager.client = std::make_unique<RavEngine::NetworkClient>();
		App::networkManager.client->Connect("127.0.0.1",6969);
		
		//what entities are allowed to spawn networked?
		App::networkManager.RegisterNetworkedEntity<TestEntity>();
		
		//create a world
		auto world = std::make_shared<TestWorld>();
		world->SetupInputs();
		AddWorld(world);
		
		SetWindowTitle(RavEngine::StrFormat("RavEngine Playground | {}", Renderer->currentBackend()).c_str());
	}
	
	int OnShutdown() override {
		return 0;
	}
};


START_APP(TestApp)
