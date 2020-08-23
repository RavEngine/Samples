#pragma once
#include <RavEngine/RavEngine_App.hpp>

class AirHockey : public RavEngine_App {
	void OnStartup(int argc, char** argv) override;
	int OnShutdown() override;
};