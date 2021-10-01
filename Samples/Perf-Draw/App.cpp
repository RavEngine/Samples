#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

using namespace std;

struct Performance_B : public RavEngine::App {
public:
	Performance_B() : App(APPNAME) {}
private:
	void OnStartup(int argc, char** argv) override;
};


void Performance_B::OnStartup(int argc, char** argv) {
	
	//unlock tickrate
	//SetMinTickTime(std::chrono::duration<double, std::milli>(0));

	// load world
	AddWorld(make_shared<PerfB_World>());

	SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
}

START_APP(Performance_B)
