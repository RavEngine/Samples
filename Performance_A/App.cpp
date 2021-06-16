#include <RavEngine/App.hpp>
#include "Level.hpp"

using namespace std;

struct Performance_A : public RavEngine::App {
public:
	Performance_A() : App("RavEngine_Sample_Performance_A") {}
private:
	void OnStartup(int argc, char** argv) override;
};


void Performance_A::OnStartup(int argc, char** argv) {
	
	//unlock tickrate
	SetMinTickTime(std::chrono::duration<double, std::milli>(0));

	// load world
	AddWorld(make_shared<PerfA_World>());

	SetWindowTitle(RavEngine::StrFormat("RavEngine Performance_A | {}", Renderer->currentBackend()).c_str());
}

START_APP(Performance_A)
