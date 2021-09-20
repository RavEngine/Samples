#include "Flagpole.hpp"
#include <RavEngine/SceneLoader.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <etl/vector.h>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>

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
    
    // load animation
    auto skeleton = RavEngine::New<SkeletonAsset>("flag.fbx");
    auto clips = RavEngine::New<AnimationAsset>("flag.fbx",skeleton);
    auto meshAssetSkinned = MeshAssetSkinned::Manager::Get("flag.fbx",skeleton);
    
    auto flagEntity = Entity::New();
    EmplaceComponent<ChildEntityComponent>(flagEntity);
    flagEntity->GetTransform()->LocalTranslateDelta(vector3(3,8,0));
    flagEntity->GetTransform()->LocalRotateDelta(vector3(PI/2,0,0));
    flagEntity->GetTransform()->LocalScaleDelta(vector3(2));
    
    auto skinnedMesh = flagEntity->EmplaceComponent<SkinnedMeshComponent>(skeleton,meshAssetSkinned);
    auto matinst = RavEngine::New<FlagMatInst>(Material::Manager::GetMaterial<FlagMat>());
    skinnedMesh->SetMaterial(matinst);
    
    Ref<Texture> tx = RavEngine::New<Texture>("flag_us.svg",1024,1024);
    matinst->SetAlbedoTexture(tx);
    
    auto animcomp = flagEntity->EmplaceComponent<AnimatorComponent>(skeleton);
    
    AnimatorComponent::State all_anim{ 0, clips };
    all_anim.isLooping = true;
    animcomp->InsertState(all_anim);
    animcomp->Goto(0,true);
    animcomp->Play();
    
    // load shaders
}
