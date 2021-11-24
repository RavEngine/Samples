#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

using namespace std;

struct LightingApp : public RavEngine::App {
	LightingApp() : App(APPNAME) {}

	void OnStartup(int argc, char** argv) final{

		App::GetRenderEngine().VideoSettings.vsync = false;
		App::GetRenderEngine().SyncVideoSettings();

		AddWorld(make_shared<Level>());

		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
};

START_APP(LightingApp)
