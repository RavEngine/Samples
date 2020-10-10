#pragma once
#include "RavEngine/App.hpp"

class AirHockey : public RavEngine::App {
	void OnStartup(int argc, char** argv) override;
	int OnShutdown() override;
};
