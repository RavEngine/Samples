#include "Flagpole.hpp"
#include <RavEngine/SceneLoader.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Texture.hpp>

using namespace RavEngine;
using namespace std;

void Flagpole::Create(){
    GameObject::Create();
    // load meshes
    SceneLoader sl("flagpole.fbx");
    FixedVector<Ref<MeshAsset>, 2> meshes;
    sl.LoadMeshes([](const PreloadedAsset& asset){
        return true;
    }, [&](Ref<MeshAsset> mesh, Ref<PBRMaterialInstance> inst, const PreloadedAsset & data){
        meshes.push_back(mesh);
    });
    auto mat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
    EmplaceComponent<StaticMesh>(meshes[0],mat);
    EmplaceComponent<StaticMesh>(meshes[1],mat);
    
    // load animation
    auto skeleton = RavEngine::New<SkeletonAsset>("flag.fbx");
    auto clips = RavEngine::New<AnimationAsset>("flag.fbx",skeleton);
    auto meshAssetSkinned = MeshAssetSkinned::Manager::Get("flag.fbx",skeleton);
    
    auto flagEntity = GetWorld()->CreatePrototype<GameObject>();
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
        mat->doubleSided = true;
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
    animcomp.InsertState(all_anim);
    animcomp.Goto(0,true);
    animcomp.Play();
    animcomp.debugEnabled = true;
    
    // load shaders
}

void Flagpole::SwitchToFlag(uint16_t idx){
    GetTransform().GetChildren()[0].GetOwner().GetComponent<SkinnedMeshComponent>().SetMaterial(flags[idx].matInst);
}

Ref<RavEngine::MaterialInstance> Flagpole::GetCurrentMaterial()
{
    return GetTransform().GetChildren()[0].GetOwner().GetComponent<SkinnedMeshComponent>().GetMaterial();
}
