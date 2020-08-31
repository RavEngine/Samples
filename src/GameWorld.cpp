#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>

Ref<Entity> cube = new Entity();

GameWorld::GameWorld()
{
	Ref<Entity> cameraActor = new Entity();
	cameraActor->AddComponent<CameraComponent>(new CameraComponent())->setActive(true);
	cameraActor->transform()->LocalTranslateDelta(vector3(0,0,5));
	//cameraActor->transform()->LocalRotateDelta(vector3(0,glm::radians(30.0),0));

	Spawn(cameraActor);

	
	auto staticMesh = cube->AddComponent<StaticMesh>(new StaticMesh());
	staticMesh->SetMaterial(new Material());
	Spawn(cube);
}

void GameWorld::posttick(float f)
{
	cube->transform()->LocalRotateDelta(vector3(0, glm::radians(2.0 * f), 0));
}
