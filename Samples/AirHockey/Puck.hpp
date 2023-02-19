#pragma once

#include <RavEngine/GameObject.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/ComponentWithOwner.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/PhysicsSolver.hpp>

//marker for querying
struct PuckComponent : public RavEngine::ComponentWithOwner{
    PuckComponent(entity_t owner) : ComponentWithOwner(owner){}
};

struct PuckScript : public RavEngine::ScriptComponent, public RavEngine::Queryable<PuckScript,RavEngine::ScriptComponent>{
    
    using RavEngine::Queryable<PuckScript,RavEngine::ScriptComponent>::GetQueryTypes;
    
    RavEngine::Array<Ref<RavEngine::AudioAsset>,4> sounds{
		RavEngine::New<RavEngine::AudioAsset>("hockeyhit1.wav"),
		RavEngine::New<RavEngine::AudioAsset>("hockeyhit2.wav"),
		RavEngine::New<RavEngine::AudioAsset>("hockeyhit3.wav"),
		RavEngine::New<RavEngine::AudioAsset>("hockeyhit4.wav")
	};
    PuckScript(entity_t owner) : ScriptComponent(owner){}
	void Tick(float scale) override{}
	void OnColliderEnter(RavEngine::PhysicsBodyComponent&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints){
		GetOwner().GetWorld()->PlaySound(RavEngine::InstantaneousAudioSource(sounds[std::rand() % 4],GetTransform().GetWorldPosition(),3));
	}
};

class Puck : public RavEngine::GameObject{
public:
    static Ref<RavEngine::PBRMaterialInstance> material;
    void Create(){
        GameObject::Create();
        RavEngine::MeshAssetOptions opt;
        opt.scale = 0.03;
        if(material == nullptr){
            material = RavEngine::New<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
            material->SetAlbedoColor({0.2,0.2,0.2,1});
        }
        auto& puckmesh = EmplaceComponent<RavEngine::StaticMesh>(RavEngine::MeshAsset::Manager::Get("HockeyPuck.obj",opt),material);
      
        auto& dyn = EmplaceComponent<RavEngine::RigidBodyDynamicComponent>(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1);
        dyn.EmplaceCollider<RavEngine::SphereCollider>(0.3,RavEngine::New<RavEngine::PhysicsMaterial>(0,0,1),vector3(0,0.3,0));
		
		//prevent puck from falling over
		dyn.SetAxisLock(RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_X | RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_Z);
		dyn.SetMass(1.0);
		
		auto lightEntity = GetWorld()->CreatePrototype<RavEngine::GameObject>();
				
		auto& light = lightEntity.EmplaceComponent<RavEngine::PointLight>();
		light.SetColorRGBA({0,0,1,1});
		light.SetIntensity(2);
		
		GetTransform().AddChild(RavEngine::ComponentHandle<RavEngine::Transform>(lightEntity));
		
		lightEntity.GetTransform().LocalTranslateDelta(vector3(0,1,0));
		
        EmplaceComponent<PuckComponent>();
		
		auto& scr = EmplaceComponent<PuckScript>();
        
        auto callbackptr = RavEngine::New<RavEngine::PhysicsCallback>();
        auto me = *this;
        callbackptr->OnColliderEnter = [me](RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints){
            me.GetComponent<PuckScript>().OnColliderEnter(other,contactPoints,numContactPoints);
        };
        
		dyn.AddReceiver(callbackptr);
    }
};
