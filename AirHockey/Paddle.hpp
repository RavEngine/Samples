#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>

class Paddle : public RavEngine::Entity{
public:
	Paddle(){
		auto mesh = AddComponent<RavEngine::StaticMesh>(new RavEngine::StaticMesh(new RavEngine::MeshAsset("HockeyPaddle.obj",0.5)));
		
		Ref<RavEngine::PBRMaterialInstance> material = new RavEngine::PBRMaterialInstance(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
		
		mesh->SetMaterial(material);
		
		//PhysX doesn't have a cylinder primitive, so we use a sphere offset upwards and lock the axes
		auto dyn = AddComponent<RavEngine::RigidBodyDynamicComponent>(new RavEngine::RigidBodyDynamicComponent());
		AddComponent<RavEngine::SphereCollider>(new RavEngine::SphereCollider(0.5,new RavEngine::PhysicsMaterial(0.3,0.3,0.1),vector3(0,0.4,0)));
		
		dyn->SetMass(2);
		dyn->SetAxisLock(
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_X |
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_Z
						 //| RavEngine::RigidBodyDynamicComponent::AxisLock::Linear_Y
						 );
	}
};
