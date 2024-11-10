#include "Flagpole.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;

void Flagpole::Create(){
    GameObject::Create();
    // load meshes

    auto mat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
    EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("flagpole"), mat);
    EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("flagpole_top"), mat);
    
    // load animation
    auto skeleton = RavEngine::New<SkeletonAsset>("flag");
    auto clips = RavEngine::New<AnimationAsset>("flag");
    auto meshAssetSkinned = MeshCollectionSkinnedManager::Get("flag");
    
    auto flagEntity = GetWorld()->Instantiate<GameObject>();
    GetTransform().AddChild(flagEntity);
    flagEntity.GetTransform().LocalTranslateDelta(vector3(0,8,0)).LocalScaleDelta(vector3(2));
    
    auto& skinnedMesh = flagEntity.EmplaceComponent<SkinnedMeshComponent>(skeleton,meshAssetSkinned);
    
    // load the flags
    struct name_file{
        std::string name;
        std::string filename;
    };
    name_file names[] = {
        {"United States","flag_us.svg"},
        {"Canada","flag_ca.svg"},
        {"Mexico","flag_mx.svg"}
    };
    for(const auto& n : names)
    {
        auto mat = RavEngine::New<FlagMatInst>(Material::Manager::Get<FlagMat>());
        Ref<Texture> tx = RavEngine::New<Texture>(n.filename,1024,1024);
        mat->SetAlbedoTexture(tx);
        flags.push_back({n.name,mat});
    }
    
    constexpr static RavEngine::CacheBase::unique_key_t flag_special_key = 1;

    // load the special flag, which uses a different shader
    {
        auto mat = RavEngine::New<FlagMatInst>(Material::Manager::GetWithKey<FlagMat>(flag_special_key, "flag_special"));
        flags.push_back({"My Room",mat});
    }
    
    SwitchToFlag(0);
    
    auto& animcomp = flagEntity.EmplaceComponent<AnimatorComponent>(skeleton);
    
    AnimatorComponent::State all_anim{ 0, clips };
    all_anim.isLooping = true;
    auto& layer = animcomp.AddLayer();
    layer.InsertState(all_anim);
    layer.Goto(0,true);
    layer.Play();
    animcomp.debugEnabled = true;
    
    // load shaders
}

void Flagpole::SwitchToFlag(uint16_t idx){
    GetTransform().GetChildren()[0].GetOwner().GetComponent<SkinnedMeshComponent>().SetMaterial(flags[idx].matInst);
}

Ref<RavEngine::MaterialInstance> Flagpole::GetCurrentMaterial()
{
    auto mat = GetTransform().GetChildren()[0].GetOwner().GetComponent<SkinnedMeshComponent>().GetMaterial();

    return mat;
}
