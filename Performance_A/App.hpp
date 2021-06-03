#pragma once
#include <RavEngine/App.hpp>

struct Performance_A : public RavEngine::App {
public:
	Performance_A() : App("RavEngine_Sample_Performance_A") {}
private:
	void OnStartup(int argc, char** argv) override;
};