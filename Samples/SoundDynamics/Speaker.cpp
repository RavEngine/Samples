#include "Speaker.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ChildEntityComponent.hpp>

using namespace RavEngine;
using namespace std;

STATIC(Speaker::speakerMesh);
STATIC(Speaker::speakerInstance);

Speaker::Speaker(Ref<AudioAsset> a) {
	// audio source
	auto sourceEntity = make_shared<Entity>();
	EmplaceComponent<ChildEntityComponent>(sourceEntity);
	auto audio = sourceEntity->EmplaceComponent<RavEngine::AudioSourceComponent>(a);

	GetTransform()->AddChild(sourceEntity->GetTransform());
	sourceEntity->GetTransform()->LocalTranslateDelta(vector3(0, 3, 0));

	// mesh
	if (!speakerMesh) {
		speakerMesh = make_shared<MeshAsset>("speaker.obj",true);
	}

	if (!speakerInstance) {
		speakerInstance = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	}
	audio->Play();
	EmplaceComponent<StaticMesh>(speakerMesh,speakerInstance);
}