#include "Game.hpp"
#include "Level.hpp"

void Game::OnStartup(int argc, char** argv){
	auto world = std::make_shared<Level>();
	world->SetupInputs();
	AddWorld(world);
	
	SetWindowTitle(RavEngine::StrFormat("RavEngine Platforms | {}", Renderer->currentBackend()).c_str());
}

START_APP(Game)
