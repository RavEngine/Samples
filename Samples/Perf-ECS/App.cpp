#include <RavEngine/App.hpp>
#include "Level.hpp"
#include "AppInfo.hpp"

using namespace std;

struct Performance_A : public RavEngine::App {
public:
	Performance_A() : App(APPNAME) {}
private:
	void OnStartup(int argc, char** argv) override;
};


void Performance_A::OnStartup(int argc, char** argv) {
	
	//unlock tickrate
	SetMinTickTime(std::chrono::duration<double, std::milli>(0));

	// load world
	AddWorld(make_shared<PerfA_World>());

    SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, Renderer->GetCurrentBackendName()).c_str());
}

START_APP(Performance_A)
