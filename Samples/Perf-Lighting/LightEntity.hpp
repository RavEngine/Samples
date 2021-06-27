#pragma once
#include <RavEngine/Component.hpp>
#include <RavEngine/Queryable.hpp>
#include <RavEngine/App.hpp>

struct CirculateComponent : public RavEngine::Component, public  RavEngine::Queryable<CirculateComponent> {
	float radius = RavEngine::Random::get(0.2,2.0);
	float speed = RavEngine::Random::get(0.2,1.0);
	float height = RavEngine::Random::get(0.2,1.2);
};

struct CirculateSystem : public RavEngine::AutoCTTI {
	inline void Tick(float fpsScale, Ref<CirculateComponent> cc, Ref<RavEngine::Transform> transform) {
		auto time = RavEngine::App::currentTime();
		transform->SetLocalPosition(vector3(std::cos(time * cc->speed) * cc->radius, std::sin(time * cc->speed) * 0.5 + 1, std::sin(time * cc->speed) * cc->radius));
	}
};

struct LightEntity : public RavEngine::Entity {
	static Ref<RavEngine::MeshAsset> lightmesh;
	LightEntity() {
		if (!lightmesh) {
			lightmesh = std::make_shared<RavEngine::MeshAsset>("sphere.obj",0.03);
		}
		auto mat = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::AccessMaterialOfType<RavEngine::PBRMaterial>());
		EmplaceComponent<RavEngine::StaticMesh>(lightmesh,mat);
		auto cc = EmplaceComponent<CirculateComponent>();
		auto light = EmplaceComponent<RavEngine::PointLight>();
		light->Intensity = cc->radius * 1.3;
		light->color = {RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),1};
		mat->SetAlbedoColor(light->color);
	}
};