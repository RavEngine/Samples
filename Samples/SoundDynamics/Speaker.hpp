#include <RavEngine/GameObject.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

struct Speaker : public RavEngine::GameObject {

	void Create(Ref<RavEngine::AudioAsset> a);

	static Ref<RavEngine::PBRMaterialInstance> speakerInstance;

};

namespace RavEngine {
	struct AudioRoom;
}

struct Stage : public RavEngine::GameObject {
	void Create();
    GameObject roomEntity;
    RavEngine::ComponentHandle<RavEngine::AudioRoom> GetRoom();
	RavEngine::Array<Ref<RavEngine::PBRMaterialInstance>, 6> wallMaterials;
};
