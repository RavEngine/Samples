#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/DebugDraw.hpp>

struct TableDebugRenderer;

class Table : public RavEngine::Entity{
public:
    virtual ~Table(){}
    Table(){
        //create the table
        auto tablemesh = EmplaceComponent<RavEngine::StaticMesh>(RavEngine::MeshAsset::Manager::GetMesh("HockeyTable.obj"));
        Ref<RavEngine::PBRMaterialInstance> matinst = std::make_shared< RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::GetMaterial<RavEngine::PBRMaterial>());
        tablemesh->SetMaterial(matinst);

        //low-friction
        Ref<RavEngine::PhysicsMaterial> physmat = std::make_shared<RavEngine::PhysicsMaterial>(0, 0, 1.5);
		Ref<RavEngine::PhysicsMaterial> floorphysmat = std::make_shared<RavEngine::PhysicsMaterial>(0.03, 0.03, 0);	//version for floor that is not bouncy

        EmplaceComponent<RavEngine::RigidBodyStaticComponent>(/*FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1*/);
        EmplaceComponent<RavEngine::BoxCollider>(vector3(3, 1.3, 5),floorphysmat);

        constexpr float height = 2.326;
        constexpr float zdist = 5;
        constexpr float xdist = 3.09;
		constexpr float width = 1.1;

        //long-axis borders, with hole for puck to fall through
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, zdist));
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(xdist/2, height, -zdist));
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, zdist));
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width/1.8, 2.098/2, 0.258/2), physmat, vector3(-xdist/2, height, -zdist));
		
        //short-axis borders
        EmplaceComponent<RavEngine::BoxCollider>(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(xdist, height, 0));
        EmplaceComponent<RavEngine::BoxCollider>(vector3(0.6/2, 2.162/2, 9.877/2), physmat, vector3(-xdist, height, 0));
		
		//prevent paddles from going through
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, zdist));
        EmplaceComponent<RavEngine::BoxCollider>(vector3(width, 0.2, 0.15), physmat, vector3(0, 2.2, -zdist));
		
		//diagonal boxes on corners
		struct cornerbox{
			float x, z, angle;
		};
		//the corners are rotated different amounts to make the different corners deflect unevenly
		constexpr cornerbox corners[] = {{3,4.5,48},{3,-4.5,-44},{-3,-4.5,40},{-3,4.5,-49}};

		for(const auto& corner : corners){
            EmplaceComponent<RavEngine::BoxCollider>(vector3(1, 1, 0.2), physmat, vector3(corner.x, height, corner.z), vector3(0,glm::radians(corner.angle),0));
		}

		//load texture
		Ref<RavEngine::Texture> t = std::make_shared<RavEngine::Texture>("HockeyTable.png");
        matinst->SetAlbedoTexture(t);
		
		//add the debug renderer
		EmplaceComponent<TableDebugRenderer>();
    }
};

struct TableDebugRenderer : public RavEngine::IDebugRenderer{
		
	void DrawDebug(RavEngine::DebugDraw& dbg) const override{
		auto boxes = GetOwner().lock()->GetAllComponentsOfType<RavEngine::BoxCollider>();
		for(const auto& box : boxes){
			std::static_pointer_cast<RavEngine::BoxCollider>(box)->DebugDraw(dbg);
		}
	}
};

