#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>

class Puck : public RavEngine::Entity{
public:
    virtual ~Puck(){};
    static Ref<RavEngine::DefaultMaterialInstance> material;
    Puck(){
        auto puckmesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPuck.obj")));
        if(material == nullptr){
            if (RavEngine::Material::Manager::HasMaterialByName("cubes")){
                material = new RavEngine::DefaultMaterialInstance(RavEngine::Material::Manager::GetMaterialByName("cubes"));
            }
            else{
                material = new RavEngine::DefaultMaterialInstance(new RavEngine::DefaultMaterial());
            }
        }
        puckmesh->SetMaterial(material);
        transform()->SetLocalScale(vector3(0.05,0.05,0.05));
    }
};
