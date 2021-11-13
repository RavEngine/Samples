#pragma once

#include <RavEngine/World.hpp>
#include <RavEngine/GameObject.hpp>

class World : public RavEngine::World{
	void OnActivate() override;
	void PostTick(float) override;
protected:
	RavEngine::GameObject cube;
};
