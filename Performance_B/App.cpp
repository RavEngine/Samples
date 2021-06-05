#include "App.hpp"
#include "Level.hpp"

using namespace std;

void Performance_B::OnStartup(int argc, char** argv) {
	
	//unlock tickrate
	//SetMinTickTime(std::chrono::duration<double, std::milli>(0));

	// load world
	AddWorld(make_shared<PerfB_World>());

	SetWindowTitle(RavEngine::StrFormat("RavEngine Performance_B | {}", Renderer->currentBackend()).c_str());
}

START_APP(Performance_B)