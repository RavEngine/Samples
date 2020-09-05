#pragma once
#include "RavEngine/RavEngine_App.hpp"

class AirHockey : public RavEngine::App {
	void OnStartup(int argc, char** argv) override;
	int OnShutdown() override;
};