#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>

struct RotationComponent : public RavEngine::Component, public RavEngine::Queryable<RotationComponent>{
	float xspeed = 0.5, yspeed = 0.2, zspeed = 0.4,
		  maxDeg = 10;
};

struct Ground : public RavEngine::Entity{
	Ground(){
		auto mat = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::GetMaterial<RavEngine::PBRMaterial>());
        RavEngine::MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
		auto mesh = RavEngine::MeshAsset::Manager::Get("ground.obj",opt);	//need to retain the mesh data in system memory 
		EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
		EmplaceComponent<RotationComponent>();
		EmplaceComponent<RavEngine::RigidBodyStaticComponent>();
		EmplaceComponent<RavEngine::MeshCollider>(mesh,std::make_shared<RavEngine::PhysicsMaterial>(0.3,0.3,0.1));
		
		// system memory copy is no longer needed
		//mesh->DeallocSystemCopy();
	}
};

struct RigidBody : public RavEngine::Entity{
	enum class BodyType{
		Sphere,
		Cube
	};
	
	RigidBody(Ref<RavEngine::PBRMaterialInstance> mat, Ref<RavEngine::MeshAsset> mesh, Ref<RavEngine::PhysicsMaterial> physmat, BodyType type){
		EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
		EmplaceComponent<RavEngine::RigidBodyDynamicComponent>();
		
		switch(type){
			case BodyType::Sphere:
				EmplaceComponent<RavEngine::SphereCollider>(1,physmat);
				break;
			case BodyType::Cube:
				EmplaceComponent<RavEngine::BoxCollider>(vector3(1,1,1),physmat);
				break;
		}
	}
};
