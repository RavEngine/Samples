#include <RavEngine/World.hpp>

namespace RavEngine {
	struct AudioAsset;
    struct AudioMIDIPlayer;
}

struct Level : public RavEngine::World {
	Level();
    RavEngine::UnorderedMap<RavEngine::Filesystem::Path,Ref<RavEngine::AudioAsset>> tracks;
    RavEngine::UnorderedMap<RavEngine::Filesystem::Path,Ref<RavEngine::AudioMIDIPlayer>> midiplayers;
	RavEngine::Array<Ref<RavEngine::Texture>,24> wallTextures;
    
    void ToggleMouse();
};
