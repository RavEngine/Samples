#include "Speaker.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AudioMIDI.hpp>
#include <RavEngine/AudioGraphAsset.hpp>

using namespace RavEngine;
using namespace std;

STATIC(Speaker::speakerInstance);

void Speaker::Create(Ref<AudioAsset> a) {
    GameObject::Create();
	// audio source
	auto sourceEntity = GetWorld()->CreatePrototype<GameObject>();
	auto& audio = sourceEntity.EmplaceComponent<RavEngine::AudioSourceComponent>(a);
	
	// mono effect graph
	auto effectGraph = New<AudioGraphAsset>(1);
	effectGraph->filters.emplace_back(New<AudioGainFilterLayer>(0.5));

	audio.SetGraph(effectGraph);


    // MIDI source
    sourceEntity.EmplaceComponent<AudioMIDISourceComponent>();
    
	GetTransform().AddChild(sourceEntity);
	sourceEntity.GetTransform().LocalTranslateDelta(vector3(0, 3, 0));

	if (!speakerInstance) {
		speakerInstance = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		auto texture = Texture::Manager::Get("speaker.png");
		speakerInstance->SetAlbedoTexture(texture);
	}
	audio.Play();
    EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("speaker.obj"),speakerInstance);
}
