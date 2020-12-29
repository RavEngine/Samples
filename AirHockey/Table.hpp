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
		constexpr float width = 1.1;

        //long-axis borders, with hole for puck to fall through
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, zdist)));
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, -zdist)));
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, zdist)));
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, -zdist)));
		
        //short-axis borders
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(xdist, height, 0)));
        AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(-xdist, height, 0)));
		
		//prevent paddles from going through
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, zdist)));
		AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, -zdist)));
		
		//diagonal boxes on corners
		struct cornerbox{
			float x, z, angle;
		};
		//the corners are rotated different amounts to make the different corners deflect unevenly
		constexpr cornerbox corners[] = {{3,4.5,48},{3,-4.5,-44},{-3,-4.5,40},{-3,4.5,-49}};

		for(const auto& corner : corners){
			AddComponent<RavEngine::BoxCollider>(new RavEngine::BoxCollider(vector3(1, 1, 0.2), physmat, vector3(corner.x, height, corner.z), vector3(0,glm::radians(corner.angle),0)));
		}

		//load texture
		Ref<RavEngine::Texture> t = new RavEngine::Texture("HockeyTable.png");
        matinst->SetAlbedoTexture(t);
    }
	
	/**
	 Displays the table's collision shapes as wireframes. Note that in release mode, debug draws are stubbed out.
	 */
	void DrawAllDebug(){
		auto boxes = GetAllComponentsOfType<RavEngine::BoxCollider>();
		for(const auto& box : boxes){
			box->DebugDraw();
		}
	}
};
