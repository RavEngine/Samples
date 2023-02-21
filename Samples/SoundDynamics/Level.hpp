#include <RavEngine/World.hpp>

namespace RavEngine {
	struct AudioAsset;
    struct AudioMIDIPlayer;
    struct AudioDataProvider;
}

struct Level : public RavEngine::World {
	Level();
    RavEngine::UnorderedMap<RavEngine::Filesystem::Path,Ref<RavEngine::AudioDataProvider>> tracks;
	RavEngine::Array<Ref<RavEngine::Texture>,24> wallTextures;
    
    void ToggleMouse();
};
