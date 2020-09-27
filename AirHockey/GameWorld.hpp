#include <RavEngine/World.hpp>

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld();

	void posttick(float) override;
};