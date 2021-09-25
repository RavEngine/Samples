#include "Speaker.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ChildEntityComponent.hpp>

using namespace RavEngine;
using namespace std;

STATIC(Speaker::speakerInstance);

Speaker::Speaker(Ref<AudioAsset> a) {
	// audio source
	auto sourceEntity = make_shared<Entity>();
	EmplaceComponent<ChildEntityComponent>(sourceEntity);
	auto audio = sourceEntity->EmplaceComponent<RavEngine::AudioSourceComponent>(a);

	GetTransform()->AddChild(sourceEntity->GetTransform());
	sourceEntity->GetTransform()->LocalTranslateDelta(vector3(0, 3, 0));

	if (!speakerInstance) {
		speakerInstance = make_shared<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		auto texture = make_shared<Texture>("speaker.png");
		speakerInstance->SetAlbedoTexture(texture);
	}
	audio->Play();
    EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetMesh("speaker.obj"),speakerInstance);
}
