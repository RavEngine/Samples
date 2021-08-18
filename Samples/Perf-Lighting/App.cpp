#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

using namespace std;

struct LightingApp : public RavEngine::App {
	LightingApp() : App(APPNAME) {}

	void OnStartup(int argc, char** argv) final{

		AddWorld(make_shared<Level>());

		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, Renderer->GetCurrentBackendName()).c_str());
	}
};

START_APP(LightingApp)