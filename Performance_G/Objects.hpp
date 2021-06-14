#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>

struct RotationComponent : public RavEngine::Component, public RavEngine::Queryable<RotationComponent>{
	float xspeed = 0.5, yspeed = 0.2, zspeed = 0.4,
		  maxDeg = 30;
};

struct Ground : public RavEngine::Entity{
	Ground(){
		auto mat = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
		auto mesh = std::make_shared<RavEngine::MeshAsset>("ground.obj",1.0,true);	//need to retain the mesh data in system memory 
		EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
		EmplaceComponent<RotationComponent>();
		EmplaceComponent<RavEngine::RigidBodyStaticComponent>();
		EmplaceComponent<RavEngine::MeshCollider>(mesh,std::make_shared<RavEngine::PhysicsMaterial>(0.3,0.3,0.1));
		
		// system memory copy is no longer needed
		//mesh->DeallocSystemCopy();
	}
};
