#pragma once

#include <RavEngine/World.hpp>

class World : public RavEngine::World{
	void OnActivate() override;
	void posttick(float) override;
protected:
	Ref<RavEngine::Entity> cube;
};
