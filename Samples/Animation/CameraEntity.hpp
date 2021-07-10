#pragma once
#include <RavEngine/Entity.hpp>
#include "Character.hpp"

struct CameraScript;

struct CameraEntity : public RavEngine::Entity {
	CameraEntity(Ref<Character>);
	
	void MoveForward(float);
	void MoveRight(float);
	void SpeedIncrement(float);
private:
	Ref<Entity> cameraEntity, cameraArmBase;
	Ref<CameraScript> cameraScript;
};
