#include "Level.hpp"
#include "Player.hpp"
#include "Speaker.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/InputManager.hpp>

using namespace RavEngine;
using namespace std;

struct InputNames {
	static constexpr char const
		* MoveForward = "MoveForward",
		* MoveRight = "MoveRight",
		* MoveUp = "MoveUp",
		* LookRight = "LookRight",
		* LookUp = "LookUp";
};

void Level::OnActivate() {
	// lights
	auto lightEntity = make_shared<Entity>();
	lightEntity->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	lightEntity->EmplaceComponent<DirectionalLight>();
	lightEntity->GetTransform()->LocalRotateDelta(vector3{glm::radians(45.0),glm::radians(45.0),0});
	Spawn(lightEntity);

	// create the audio room
	auto stage = make_shared<Stage>();
	Spawn(stage);

	// load audio
	auto audio = make_shared<AudioAsset>("The Entertainer.mp3");

	// create speakers
	auto speaker1 = make_shared<Speaker>(audio);
	speaker1->GetTransform()->LocalTranslateDelta(vector3(0,0,-2));
	Spawn(speaker1);

	// create player 
	auto player = make_shared<Player>();
	Spawn(player);

	// setup inputs
	auto im = App::inputManager = make_shared<InputManager>();
	
	im->AddAxisMap(InputNames::MoveForward, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap(InputNames::MoveRight, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);

	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S,-1);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A, -1);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_SPACE);
	im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT, -1);

	im->AddAxisMap(InputNames::LookRight,Special::MOUSEMOVE_XVEL,-1);
	im->AddAxisMap(InputNames::LookUp,Special::MOUSEMOVE_YVEL,-1);

	im->BindAxis(InputNames::MoveForward, player, &Player::MoveForward, CID::ANY);
	im->BindAxis(InputNames::MoveRight, player, &Player::MoveRight, CID::ANY);
	im->BindAxis(InputNames::MoveUp, player, &Player::MoveUp, CID::ANY);
	im->BindAxis(InputNames::LookRight, player, &Player::LookRight, CID::ANY);
	im->BindAxis(InputNames::LookUp, player, &Player::LookUp, CID::ANY);

	// initialize physics
	InitPhysics();
}

Level::Level() {

}
