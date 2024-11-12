#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Ref.hpp>
#include <RavEngine/Tween.hpp>

namespace RavEngine {
    struct MeshCollectionSkinned;
    struct MeshCollectionStatic;
}

struct CharacterScript : public RavEngine::ComponentWithOwner {

    RavEngine::ComponentHandle<RavEngine::AnimatorComponent> animator;
    RavEngine::ComponentHandle<RavEngine::RigidBodyDynamicComponent> rigidBody;
    RavEngine::Tween<decimalType> waveInfluenceTween;
    bool tweenEnabled = false;
    bool controlsEnabled = true;
    constexpr static decimalType sprintSpeed = 2.5, walkSpeed = 2;

    int16_t groundCounter = 0;

    CharacterScript(RavEngine::Entity owner, decltype(animator) a, decltype(rigidBody) r);

    bool OnGround() const;

    void Tick(float fpsScale);

    void Move(const vector3& dir, decimalType speedMultiplier);

    void Jump();

    void Pound();

    void OnColliderEnter(RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints);

    void OnColliderExit(RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints);

    void StartPounding();
    
    void Wave();

};

namespace RavEngine {
    class MeshAssetSkinned;
    class PBRMaterialInstance;
    class SkeletonAsset;
}


struct Character : public RavEngine::GameObject {
	void Create(Ref<RavEngine::MeshCollectionSkinned> skinnedMesh, Ref<RavEngine::MeshCollectionStatic> handMesh, Ref<RavEngine::PBRMaterialInstance> handMatInst, Ref<RavEngine::PBRMaterialInstance> materialInstance, Ref<RavEngine::SkeletonAsset> skeleton);
	void Move(const vector3&, decimalType speedMultiplier = 0);
	void Jump();
	void Pound();
    void Wave();
    
    // anything that has these 2 calls
    // can be a target for input manager
    // however, the memory location of the
    // bound object must be stable
    inline auto get_id() const{
        return id;
    }
    
    inline Character* get() const{
        return const_cast<Character*>(this);
    }
    
private:
    RavEngine::ComponentHandle<RavEngine::RigidBodyDynamicComponent> rigidBody;
    RavEngine::ComponentHandle<CharacterScript> script;
};

struct CharacterScriptRunner : public RavEngine::AutoCTTI {
    void operator()(CharacterScript&);
};
