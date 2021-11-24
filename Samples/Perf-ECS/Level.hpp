#include <RavEngine/World.hpp>

struct PerfA_World : public RavEngine::World {
	void OnActivate() override;	//invoked automatically when world is made active
	void SetECSMode(int mode);
	int lastMode = -1;
};