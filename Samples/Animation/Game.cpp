#include "Level.hpp"
#include <RavEngine/App.hpp>
#include "AppInfo.hpp"

class Game : public RavEngine::App{
public:
    Game() : RavEngine::App(APPNAME){}
    void OnStartup(int argc, char** argv) override;
};


void Game::OnStartup(int argc, char** argv){
	auto world = std::make_shared<Level>();
	world->SetupInputs();
	AddWorld(world);
	
	SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, Renderer->currentBackend()).c_str());
}

START_APP(Game)
