#pragma once

#include <RavEngine/App.hpp>

class Game : public RavEngine::App{
public:
	Game() : RavEngine::App("RavEngine_Sample_Platforms"){}
	void OnStartup(int argc, char** argv) override;
};
