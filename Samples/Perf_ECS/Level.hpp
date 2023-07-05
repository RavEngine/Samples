#include <RavEngine/World.hpp>

struct PerfA_World : public RavEngine::World {
	PerfA_World();
	void SetECSMode(int mode);
	int lastMode = -1;
};
