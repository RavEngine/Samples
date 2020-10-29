#pragma once 

#include "WorldTest.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/WeakRef.hpp>
#include <RavEngine/SharedObject.hpp>
#include <cassert>

class TestApp : public RavEngine::App{
public:
	TestApp() : App("RavEngine_Sample_Playground"){}
private:
	void OnStartup(int argc, char** argv) override{
		{
			WeakRef<RavEngine::SharedObject> w;
			{
				Ref<RavEngine::SharedObject> re(new RavEngine::SharedObject());
				w = re;
				assert(w.get() == re.get());
			}
			assert(w.get() == nullptr);
		}

		//setup video settings
		RavEngine::RenderEngine::VideoSettings.vsync = true;
		RavEngine::RenderEngine::VideoSettings.width = 800;
		RavEngine::RenderEngine::VideoSettings.height = 480;

		//create a world
		currentWorld = new TestWorld();
	}

	int OnShutdown() override {
		return 0;
	}
};
