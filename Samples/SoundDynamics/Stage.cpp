#include "Speaker.hpp"
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/SceneLoader.hpp>

using namespace std;
using namespace RavEngine;

void Stage::Create() {
    GameObject::Create();
    roomEntity = GetWorld()->CreatePrototype<GameObject>();

	auto& audioRoom = roomEntity.EmplaceComponent<GeometryAudioSpace>();
	audioRoom.SetAudioSourceRadius(50);
	audioRoom.SetMeshRadius(50);

	GetTransform().AddChild(roomEntity);
    

    Array<string_view, 6> faceOrder{
		"wall_negx",
		"wall_posx",
		"floor",
		"ceiling",
		"wall_negz",
		"wall_posz"
	};

	// load room
	SceneLoader loader("room.fbx");
	loader.LoadMeshes([&](const PreloadedAsset& pr) -> bool {
		// we want to load all meshes in this case
		return true;

	}, [&](Ref<MeshAsset> rm, Ref<PBRMaterialInstance>, const PreloadedAsset& pr) {
		auto pos = std::distance(faceOrder.begin(),std::find(faceOrder.begin(), faceOrder.end(), pr.name));
		auto inst = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		EmplaceComponent<StaticMesh>(rm, LitMeshMaterialInstance(inst));
		this->wallMaterials[pos] = inst;
	});

}
