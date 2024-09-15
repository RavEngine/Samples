#include "Speaker.hpp"
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace std;
using namespace RavEngine;

constexpr static bool useGeometrySpace = false;

void Stage::Create() {
    GameObject::Create();
    roomEntity = GetWorld()->Instantiate<GameObject>();

	if constexpr (useGeometrySpace) {
		auto& audioRoom = roomEntity.EmplaceComponent<GeometryAudioSpace>();
		audioRoom.SetAudioSourceRadius(50);
		audioRoom.SetMeshRadius(50);
	}
	else {
		auto& audioRoom = roomEntity.EmplaceComponent<BoxReverbationAudioSpace>();
		audioRoom.SetHalfExts({50,50,50});
	}

	GetTransform().AddChild(roomEntity);
    

    Array<string_view, 6> faceOrder{
		"wall_negx",
		"wall_posx",
		"floor",
		"ceiling",
		"wall_negz",
		"wall_posz"
	};
    
    for(const auto& name : faceOrder){
        auto pos = std::distance(faceOrder.begin(),std::find(faceOrder.begin(), faceOrder.end(), name));
        auto inst = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        auto rm = MeshCollectionStaticManager::Get(std::string(name));
        EmplaceComponent<StaticMesh>(rm, inst);
        this->wallMaterials[pos] = inst;
    }

}
