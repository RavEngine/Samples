#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/CameraComponent.hpp>

struct Camera : public RavEngine::Entity{
	Camera(){
		AddComponent<RavEngine::CameraComponent>(new RavEngine::CameraComponent())->setActive(true);
	}
};

