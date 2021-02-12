#pragma once

#include <RavEngine/App.hpp>

struct App : public RavEngine::App{
	App() : RavEngine::App("RavEngine_Sample_GUIKitchenSink"){}
	void OnStartup(int argc, char** argv) override;
};
