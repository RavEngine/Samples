#include "Flagpole.hpp"
#include <RavEngine/SceneLoader.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <etl/vector.h>

using namespace RavEngine;
using namespace std;

Flagpole::Flagpole(){
    // load meshes
    SceneLoader sl("flagpole.fbx");
    etl::vector<Ref<MeshAsset>, 2> meshes;
    sl.LoadMeshes([](const PreloadedAsset& asset){
        return true;
    }, [&](Ref<MeshAsset> mesh, const PreloadedAsset & data){
        meshes.push_back(mesh);
    });
    
    EmplaceComponent<StaticMesh>(meshes[0],RavEngine::New<PBRMaterialInstance>(Material::Manager::GetMaterial<PBRMaterial>()));
    EmplaceComponent<StaticMesh>(meshes[1],RavEngine::New<PBRMaterialInstance>(Material::Manager::GetMaterial<PBRMaterial>()));
    
    // load shaders
}
