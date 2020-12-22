#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

class Table : public RavEngine::Entity{
public:
    virtual ~Table(){}
    Table(){
        //create the table
        auto tablemesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyTable.obj")));
        Ref<RavEngine::PBRMaterialInstance> matinst = new RavEngine::PBRMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
        tablemesh->SetMaterial(matinst);

        //low-friction
        Ref<RavEngine::PhysicsMaterial> physmat = new RavEngine::PhysicsMaterial(0, 0, 1);
		Ref<RavEngine::PhysicsMaterial> floorphysmat = new RavEngine::PhysicsMaterial(0.03, 0.03, 0);	//version for floor that is not bouncy

        AddComponent<RavEngine::RigidBodyStaticComponent>(new RavEngine::RigidBodyStaticComponent());
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(3, 1.3, 5),floorphysmat));

        constexpr float height = 2.326;
        constexpr float zdist = 5;
        constexpr float xdist = 3.09;

        //long-axis borders
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(3, 2.098/2, 0.258/2), physmat, vector3(0, height, zdist)));
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(3, 2.098/2, 0.258/2), physmat, vector3(0, height, -zdist)));
        //short-axis borders
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(0.194/2, 2.162/2, 9.877/2), physmat, vector3(xdist, height, 0)));
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(0.194/2, 2.162/2, 9.877/2), physmat, vector3(-xdist, height, 0)));

		Ref<RavEngine::Texture> t = new RavEngine::Texture("HockeyTable.png");
        matinst->SetAlbedoTexture(t);
    }
};
