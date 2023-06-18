#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>

struct RotationComponent : public RavEngine::AutoCTTI{
	float xspeed = 0.5, yspeed = 0.2, zspeed = 0.4, maxDeg = 10;
};

struct Ground : public RavEngine::GameObject{
	void Create(){
        GameObject::Create();
		auto mat = RavEngine::New<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
        RavEngine::MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
		auto mesh = RavEngine::MeshAsset::Manager::Get("ground.obj",opt);	//need to retain the mesh data in system memory 
		EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
		EmplaceComponent<RotationComponent>();
		auto& rs = EmplaceComponent<RavEngine::RigidBodyStaticComponent>();
        rs.EmplaceCollider<RavEngine::MeshCollider>(mesh,RavEngine::New<RavEngine::PhysicsMaterial>(0.3,0.3,0.1));
		
		// system memory copy is no longer needed
		//mesh->DeallocSystemCopy();
	}
};

struct RigidBody : public RavEngine::GameObject{
	enum class BodyType{
		Sphere,
		Cube
	};
	
	void Create(Ref<RavEngine::PBRMaterialInstance> mat, Ref<RavEngine::MeshAsset> mesh, Ref<RavEngine::PhysicsMaterial> physmat, BodyType type){
        GameObject::Create();
		EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
		auto& rd = EmplaceComponent<RavEngine::RigidBodyDynamicComponent>();
		
		switch(type){
			case BodyType::Sphere:
				rd.EmplaceCollider<RavEngine::SphereCollider>(1,physmat);
				break;
			case BodyType::Cube:
                rd.EmplaceCollider<RavEngine::BoxCollider>(vector3(1,1,1),physmat);
				break;
		}
	}
};
