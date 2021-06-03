#include "App.hpp"
#include "Level.hpp"

using namespace std;

void Performance_A::OnStartup(int argc, char** argv) {
	
	//unlock tickrate
	SetMinTickTime(std::chrono::duration<double, std::milli>(0));

	// load world
	AddWorld(make_shared<PerfA_World>());

	SetWindowTitle(fmt::format("RavEngine Performance_A | {}", Renderer->currentBackend()).c_str());
}

START_APP(Performance_A)