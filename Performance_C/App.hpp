#pragma once
#include "RavEngine/App.hpp"

class Performance_C : public RavEngine::App{
public:
	Performance_C() : App("RavEngine_Sample_Performance_C"){}
private:
	void OnStartup(int argc, char** argv) override;
};
