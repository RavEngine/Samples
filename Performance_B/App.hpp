#pragma once
#include <RavEngine/App.hpp>

struct Performance_B : public RavEngine::App {
public:
	Performance_B() : App("RavEngine_Sample_Performance_B") {}
private:
	void OnStartup(int argc, char** argv) override;
};