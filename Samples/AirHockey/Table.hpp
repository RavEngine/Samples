#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/AudioMeshAsset.hpp>

struct TableDebugRenderer;

class Table : public RavEngine::GameObject{
public:
    void Create(){
        GameObject::Create();
        //create the table
        Ref<RavEngine::PBRMaterialInstance> matinst = RavEngine::New< RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
        auto tableMeshAsset = RavEngine::MeshAsset::Manager::Get("HockeyTable.fbx", RavEngine::MeshAssetOptions{.keepInSystemRAM = true});
        auto& tablemesh = EmplaceComponent<RavEngine::StaticMesh>(tableMeshAsset, RavEngine::LitMeshMaterialInstance(matinst));
        
        //low-friction
        Ref<RavEngine::PhysicsMaterial> physmat = RavEngine::New<RavEngine::PhysicsMaterial>(0, 0, 1.5);
		Ref<RavEngine::PhysicsMaterial> floorphysmat = RavEngine::New<RavEngine::PhysicsMaterial>(0.03, 0.03, 0);	//version for floor that is not bouncy

        auto& dyn = EmplaceComponent<RavEngine::RigidBodyStaticComponent>(/*FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1*/);
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(3, 1.3, 5),floorphysmat);

        constexpr float height = 2.326;
        constexpr float zdist = 5;
        constexpr float xdist = 3.09;
		constexpr float width = 1.1;

        //long-axis borders, with hole for puck to fall through
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, zdist));
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, -zdist));
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, zdist));
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, -zdist));
		
        //short-axis borders
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(xdist, height, 0));
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(-xdist, height, 0));
		
		//prevent paddles from going through
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, zdist));
        dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, -zdist));
		
		//diagonal boxes on corners
		struct cornerbox{
			float x, z, angle;
		};
		//the corners are rotated different amounts to make the different corners deflect unevenly
		constexpr cornerbox corners[] = {{3,4.5,48},{3,-4.5,-44},{-3,-4.5,40},{-3,4.5,-49}};

		for(const auto& corner : corners){
            dyn.EmplaceCollider<RavEngine::BoxCollider>(vector3(1, 1, 0.2), physmat, vector3(corner.x, height, corner.z), vector3(0,deg_to_rad(corner.angle),0));
		}

		//load texture
		Ref<RavEngine::Texture> t = RavEngine::New<RavEngine::Texture>("HockeyTable.png");
        matinst->SetAlbedoTexture(t);

        auto audioMeshAsset = RavEngine::New<RavEngine::AudioMeshAsset>(tableMeshAsset);

    }
};
