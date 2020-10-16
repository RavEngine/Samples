#pragma once
#include "RavEngine/App.hpp"

class AirHockey : public RavEngine::App {
public:
	AirHockey() : App("RavEngine_Sample_AirHockey"){}
private:
	void OnStartup(int argc, char** argv) override;
	int OnShutdown() override;
};
