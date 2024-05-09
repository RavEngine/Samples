#include <RavEngine/World.hpp>
#include <RavEngine/Filesystem.hpp>

namespace RavEngine {
	struct AudioAsset;
    struct AudioMIDIPlayer;
    struct AudioDataProvider;
}

struct Level : public RavEngine::World {
	Level();
    RavEngine::UnorderedMap<RavEngine::Filesystem::Path,Ref<RavEngine::AudioDataProvider>> tracks;
    
    void ToggleMouse();
};
