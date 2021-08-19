#include <RavEngine/Entity.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

struct Speaker : public RavEngine::Entity {

	Speaker(Ref<RavEngine::AudioAsset> a);

	static Ref<RavEngine::MeshAsset> speakerMesh;
	static Ref<RavEngine::PBRMaterialInstance> speakerInstance;
};

struct Stage : public RavEngine::Entity {
	Stage();
};