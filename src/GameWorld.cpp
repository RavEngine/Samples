#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>

GameWorld::GameWorld()
{
	Ref<Entity> cameraActor = new Entity();
	cameraActor->AddComponent<CameraComponent>(new CameraComponent())->setActive(true);
	cameraActor->transform()->LocalTranslateDelta(vector3(0,0,0));

	Spawn(cameraActor);

	Ref<Entity> cube = new Entity();
	auto staticMesh = cube->AddComponent<StaticMesh>(new StaticMesh());
	staticMesh->SetMaterial(new Material());
	cube->transform()->LocalTranslateDelta(vector3(0,0,-5));
	Spawn(cube);
}

void GameWorld::posttick(float)
{
	
}
