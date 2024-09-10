#include "Speaker.hpp"
#include <RavEngine/StaticMesh.hpp>
#include "AudioMIDI.hpp"
#include <RavEngine/AudioGraphAsset.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;

STATIC(Speaker::speakerInstance);

void Speaker::Create(Ref<AudioDataProvider> a) {
    GameObject::Create();
	// audio source
	auto sourceEntity = GetWorld()->Instantiate<GameObject>();
	auto& audio = sourceEntity.EmplaceComponent<RavEngine::AudioSourceComponent>(a);

    
	GetTransform().AddChild(sourceEntity);
	sourceEntity.GetTransform().LocalTranslateDelta(vector3(0, 3, 0));

	if (!speakerInstance) {
		speakerInstance = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		auto texture = Texture::Manager::Get("speaker.png");
		speakerInstance->SetAlbedoTexture(texture);
	}
    EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("speaker"), speakerInstance);
}
