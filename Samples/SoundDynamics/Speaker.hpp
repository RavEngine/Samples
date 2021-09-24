#include <RavEngine/Entity.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

struct Speaker : public RavEngine::Entity {

	Speaker(Ref<RavEngine::AudioAsset> a);

	static Ref<RavEngine::PBRMaterialInstance> speakerInstance;

};

namespace RavEngine {
	struct AudioRoom;
}

struct Stage : public RavEngine::Entity {
	Stage();
	Ref<RavEngine::AudioRoom> GetRoom();
    Array<Ref<RavEngine::PBRMaterialInstance>, 6> wallMaterials;
};
