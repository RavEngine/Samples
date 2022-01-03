#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include "Level.hpp"

using namespace RavEngine;

struct SoundDynamics : public RavEngine::App {
	SoundDynamics() : App(APPNAME) {}
	void OnStartup(int argc, char** argv) final {
		auto world = RavEngine::New<Level>();
		AddWorld(world);

		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
};

START_APP(SoundDynamics)
