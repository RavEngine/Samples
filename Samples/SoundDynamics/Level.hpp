#include <RavEngine/World.hpp>

struct Level : public RavEngine::World {
	void OnActivate() final;
	Level();
};