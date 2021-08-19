#include "Level.hpp"
#include "Player.hpp"
#include "Speaker.hpp"


using namespace RavEngine;
using namespace std;

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
	auto audio = make_shared<AudioAsset>("creative2.ogg");

	// create speakers
	auto speaker1 = make_shared<Speaker>(audio);
	speaker1->GetTransform()->LocalTranslateDelta(vector3(0,0,-5));
	Spawn(speaker1);

	auto player = make_shared<Player>();
	Spawn(player);
}

Level::Level() {

}
