#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/Material.hpp>

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
        auto puckmesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPuck.obj")));
        if(material == nullptr){
			material = new RavEngine::DefaultMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::DefaultMaterial>());
        }
        puckmesh->SetMaterial(material);
		AddComponent<BasicScript>(new BasicScript());
        transform()->SetLocalScale(vector3(0.05,0.05,0.05));
    }
};
