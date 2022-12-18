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
	auto effect = effectGraph->CreateNode<lab::GainNode>();
	effect->gain()->setValue(0.1);
	effectGraph->Connect(effectGraph->GetInputNode(), effect);
	effectGraph->Connect(effect, effectGraph->GetOutputNode());

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
