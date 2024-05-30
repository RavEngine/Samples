#pragma once

#include <RavEngine/World.hpp>
#include <list>
#include "Character.hpp"
#include "CameraEntity.hpp"

class Level : public RavEngine::World{
public:
	Level();
	void ChangeChar();
	void PostTick(float) final;
private:
	std::vector<Character> characters;
	uint8_t currentChar = 0;
	CameraEntity camera;
};
