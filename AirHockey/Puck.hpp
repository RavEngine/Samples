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
    static Ref<RavEngine::DefaultMaterialInstance> material;
    Puck(){
        auto puckmesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPuck.obj",0.03)));
        if(material == nullptr){
			material = new RavEngine::DefaultMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::DefaultMaterial>());
        }
        puckmesh->SetMaterial(material);
		AddComponent<BasicScript>(new BasicScript());
        AddComponent<RavEngine::RigidBodyDynamicComponent>(new RavEngine::RigidBodyDynamicComponent());
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(0.5,0.5,0.5),new RavEngine::PhysicsMaterial(0.5,0.5,0.5)));
    }
};
