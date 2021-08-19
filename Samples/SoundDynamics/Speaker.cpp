#include "Speaker.hpp"
#include <RavEngine/StaticMesh.hpp>

using namespace RavEngine;
using namespace std;

STATIC(Speaker::speakerMesh);
STATIC(Speaker::speakerInstance);

Speaker::Speaker(Ref<AudioAsset> a) {
	// audio source
	auto audio = EmplaceComponent<RavEngine::AudioSourceComponent>(a);

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