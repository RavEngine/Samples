#pragma once

#include <RavEngine/World.hpp>

class Level : public RavEngine::World{
public:
	void SetupInputs();
private:
	void posttick(float) override;
	Ref<RavEngine::Entity> cube;
};
