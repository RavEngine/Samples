#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>

class Paddle : public RavEngine::Entity{
public:
	static Ref<RavEngine::PBRMaterialInstance> material;
	Paddle(){
		auto mesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPaddle.obj",0.5)));
		
		if (material.isNull()){
			material = new RavEngine::PBRMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
			material->SetAlbedoColor({1,0,0,1});
		}
		mesh->SetMaterial(material);
		
		AddComponent<RavEngine::RigidBodyStaticComponent>(new RavEngine::RigidBodyStaticComponent());
		AddComponent<RavEngine::CapsuleCollider>(new RavEngine::CapsuleCollider(0.5,0.1,new RavEngine::PhysicsMaterial(0.5,0.5,0.5),vector3(0,0,0),vector3(0,0,glm::radians(90.0))));
	}
};
