#pragma once

#include <RavEngine/World.hpp>
#include <list>

class Level : public RavEngine::World{
public:
	Level();
	void PostTick(float) final;
};
