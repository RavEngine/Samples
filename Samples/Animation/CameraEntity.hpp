#pragma once
#include <RavEngine/Entity.hpp>
#include "Character.hpp"

struct CameraEntity : public RavEngine::Entity {
	CameraEntity(Ref<Character>);
private:
	Ref<Character> target;
};