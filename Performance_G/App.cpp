#include <RavEngine/App.hpp>
#include "Level.hpp"

struct App : public RavEngine::App{
	App() : RavEngine::App("RavEngine_Sample_Performance_G"){}
	void OnStartup(int argc, char** argv) override{
		AddWorld(std::make_shared<Level>());
		
		SetWindowTitle(RavEngine::StrFormat("RavEngine Performance_G | {}", Renderer->currentBackend()).c_str());
	}
};

START_APP(App)
