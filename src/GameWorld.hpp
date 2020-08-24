#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld() {
		Ref<Entity> cameraActor = new Entity();
		cameraActor->AddComponent<CameraComponent>(new CameraComponent());

		Spawn(cameraActor);
	}
};