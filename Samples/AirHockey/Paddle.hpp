#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/PhysicsSolver.hpp>

class Paddle : public RavEngine::Entity{
public:
	Paddle(const RavEngine::ColorRGBA& color){
        RavEngine::MeshAssetOptions opt;
        opt.scale = 0.5;
        auto mesh = EmplaceComponent<RavEngine::StaticMesh>(RavEngine::MeshAsset::Manager::Get("HockeyPaddle.obj",opt));
		
		Ref<RavEngine::PBRMaterialInstance> material = std::make_shared< RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
		material->SetAlbedoColor(color);
		mesh->SetMaterial(material);
		
		//PhysX doesn't have a cylinder primitive, so we use a sphere offset upwards and lock the axes
		auto dyn = EmplaceComponent<RavEngine::RigidBodyDynamicComponent>(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1);
        EmplaceComponent<RavEngine::SphereCollider>(0.5,std::make_shared<RavEngine::PhysicsMaterial>(0.3,0.3,0.1),vector3(0,0.4,0));
		
		dyn->SetMass(2);
		dyn->SetAxisLock(
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_X |
						 RavEngine::RigidBodyDynamicComponent::AxisLock::Angular_Z
						 //| RavEngine::RigidBodyDynamicComponent::AxisLock::Linear_Y
						 );
		
		
		auto light = EmplaceComponent<RavEngine::PointLight>();
		light->color = color;
		light->Intensity = 2;
	}
};
