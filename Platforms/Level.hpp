#pragma once

#include <RavEngine/World.hpp>
#include <list>

class Level : public RavEngine::World{
public:
	void SetupInputs();
private:
	void posttick(float) override;
	std::list<Ref<RavEngine::Entity>> cubes;
};
