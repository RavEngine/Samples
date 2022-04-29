#include "Speaker.hpp"
#include <RavEngine/AudioRoom.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/SceneLoader.hpp>

using namespace std;
using namespace RavEngine;

void Stage::Create() {
    GameObject::Create();
    roomEntity = GetWorld()->CreatePrototype<GameObject>();

	auto& audioRoom = roomEntity.EmplaceComponent<AudioRoom>();
	audioRoom.SetRoomDimensions(vector3(20, 10, 20));

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
		EmplaceComponent<StaticMesh>(rm, inst);
		this->wallMaterials[pos] = inst;
	});
	GetTransform().LocalTranslateDelta(vector3(0,audioRoom.GetRoomDimensions().y / 2,0));

}
