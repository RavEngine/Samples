#pragma once
#include <RavEngine/Entity.hpp>
#include "Character.hpp"

struct CameraEntity : public RavEngine::Entity {
	CameraEntity(Ref<Character>);
	
	void MoveForward(float);
	void MoveRight(float);
private:
	Ref<Character> target;
};
