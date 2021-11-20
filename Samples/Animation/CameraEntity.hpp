#pragma once
#include <RavEngine/GameObject.hpp>
#include "Character.hpp"

struct CameraScript;

struct CameraEntity : public RavEngine::GameObject {
	void Create(Character);
	
	void MoveForward(float);
	void MoveRight(float);
	void SpeedIncrement(float);
private:
	RavEngine::GameObject cameraEntity, cameraArmBase;
    RavEngine::ComponentHandle<CameraScript> cameraScript;
};
