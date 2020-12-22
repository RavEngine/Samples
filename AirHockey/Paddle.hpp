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
		
		auto dyn = AddComponent<RavEngine::RigidBodyDynamicComponent>(new RavEngine::RigidBodyDynamicComponent());
		AddComponent<RavEngine::CapsuleCollider>(new RavEngine::CapsuleCollider(0.5,0.1,new RavEngine::PhysicsMaterial(0.3,0.3,1),vector3(0,0.3,0),vector3(0,0,glm::radians(90.0))));
		
		dyn->SetMass(2);
		dyn->SetAxisLock(
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_X |
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_Z
						 //| RavEngine::RigidBodyDynamicComponent::AxisLock::Linear_Y
						 );
	}
};
