#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/Format.hpp>
#include <RavEngine/StartApp.hpp>

using namespace std;

struct LightingApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final{

		App::GetRenderEngine().VideoSettings.vsync = false;
		App::GetRenderEngine().SyncVideoSettings();

		AddWorld(RavEngine::New<Level>());

		SetWindowTitle(RavEngine::VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }

	bool NeedsAudio() const final {
		return false;
	}
};

START_APP(LightingApp)
