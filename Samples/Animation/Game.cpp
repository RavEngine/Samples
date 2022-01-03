#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

class Game : public RavEngine::App{
public:
    Game() : RavEngine::App(APPNAME){}
    void OnStartup(int argc, char** argv) override;
};


void Game::OnStartup(int argc, char** argv){
	AddWorld(RavEngine::New<Level>());
	
	SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
}

START_APP(Game)
