#pragma once

#include <RavEngine/World.hpp>
#include <list>

class Level : public RavEngine::World{
public:
	void SetupInputs();
	void PostTick(float) final;
};
