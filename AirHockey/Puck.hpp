#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>

class BasicScript : public RavEngine::ScriptComponent{
public:
	void Tick(float scale) override{
		//puck logic goes here
	}
};

class Puck : public RavEngine::Entity{
public:
    virtual ~Puck(){};
    static Ref<RavEngine::PBRMaterialInstance> material;
    Puck(){
        auto puckmesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPuck.obj",0.03)));
        if(material == nullptr){
			material = new RavEngine::PBRMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
			material->SetAlbedoColor({0.2,0.2,0.2,1});
        }
        puckmesh->SetMaterial(material);
		AddComponent<BasicScript>(new BasicScript());
        AddComponent<RavEngine::RigidBodyDynamicComponent>(new RavEngine::RigidBodyDynamicComponent());
		AddComponent<RavEngine::SphereCollider>(new RavEngine::SphereCollider(0.3,new RavEngine::PhysicsMaterial(0.5,0.5,0.5)));
    }
};
