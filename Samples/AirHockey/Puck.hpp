#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioSource.hpp>

//marker for querying
class PuckComponent : public RavEngine::Component, public RavEngine::Queryable<PuckComponent>{};

struct PuckScript : public RavEngine::ScriptComponent, public RavEngine::IPhysicsActor{
	std::array<Ref<RavEngine::AudioAsset>,4> sounds{
		std::make_shared<RavEngine::AudioAsset>("hockeyhit1.wav"),
		std::make_shared<RavEngine::AudioAsset>("hockeyhit2.wav"),
		std::make_shared<RavEngine::AudioAsset>("hockeyhit3.wav"),
		std::make_shared<RavEngine::AudioAsset>("hockeyhit4.wav")
	};
	void Tick(float scale) override{}
	void OnColliderEnter(const WeakRef<RavEngine::PhysicsBodyComponent>&) override{
		GetWorld()->PlaySound(RavEngine::InstantaneousAudioSource(sounds[std::rand() % 4],transform()->GetWorldPosition(),3));
	}
};

class Puck : public RavEngine::Entity{
public:
    virtual ~Puck(){};
    static Ref<RavEngine::PBRMaterialInstance> material;
    Puck(){
        auto puckmesh = EmplaceComponent<RavEngine::StaticMesh>(std::make_shared<RavEngine::MeshAsset>("HockeyPuck.obj",0.03));
        if(material == nullptr){
			material = std::make_shared< RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
			material->SetAlbedoColor({0.2,0.2,0.2,1});
        }
        puckmesh->SetMaterial(material);
        auto dyn = EmplaceComponent<RavEngine::RigidBodyDynamicComponent>(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1);
        EmplaceComponent<RavEngine::SphereCollider>(0.3,std::make_shared<RavEngine::PhysicsMaterial>(0,0,1),vector3(0,0.3,0));
		
		//prevent puck from falling over
		dyn->SetAxisLock(RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_X | RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_Z);
		dyn->SetMass(1.0);
		
		Ref<Entity> lightEntity = std::make_shared<Entity>();
		
        EmplaceComponent<RavEngine::ChildEntityComponent>(lightEntity);
		
		auto light = lightEntity->EmplaceComponent<RavEngine::PointLight>();
		light->color = {0,0,1,1};
		light->Intensity = 2;
		
		transform()->AddChild(lightEntity->transform());
		
		lightEntity->transform()->LocalTranslateDelta(vector3(0,1,0));
		
        EmplaceComponent<PuckComponent>();
		
		auto scr = EmplaceComponent<PuckScript>();
		dyn->AddReceiver(scr);
    }
};
