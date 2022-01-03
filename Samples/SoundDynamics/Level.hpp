#include <RavEngine/World.hpp>

namespace RavEngine {
	struct AudioAsset;
}

struct Level : public RavEngine::World {
	Level();
	RavEngine::Vector<Ref<RavEngine::AudioAsset>> tracks;
	RavEngine::Array<Ref<RavEngine::Texture>,24> wallTextures;
    
    void ToggleMouse();
};
