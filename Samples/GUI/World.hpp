#pragma once

#include <RavEngine/World.hpp>
#include <RavEngine/GameObject.hpp>

struct World : public RavEngine::World{
	World();
	void PostTick(float) override;
private:
	RavEngine::GameObject cube;
};
