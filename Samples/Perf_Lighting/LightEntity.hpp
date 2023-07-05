#pragma once
#include <RavEngine/Queryable.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/GameObject.hpp>

struct CirculateComponent : public RavEngine::AutoCTTI {
	float radius = RavEngine::Random::get(0.2,2.0);
	float speed = RavEngine::Random::get(0.2,1.0);
	float height = RavEngine::Random::get(0.2,1.2);
};

struct CirculateSystem : public RavEngine::AutoCTTI {
	inline void operator()(const CirculateComponent& cc, RavEngine::Transform& transform) const{
		auto time = RavEngine::GetApp()->GetCurrentTime();
		transform.SetLocalPosition(vector3(std::cos(time * cc.speed) * cc.radius, std::sin(time * cc.speed) * 0.5 + 1, std::sin(time * cc.speed) * cc.radius));
	}
};

struct LightEntity : public RavEngine::GameObject {
	void Create() {
        GameObject::Create();
		auto mat = RavEngine::New<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
        RavEngine::MeshAssetOptions opt;
        opt.scale = 0.03;
        EmplaceComponent<RavEngine::StaticMesh>(RavEngine::MeshAsset::Manager::Get("sphere.obj",opt),mat);
		auto& cc = EmplaceComponent<CirculateComponent>();
		auto& light = EmplaceComponent<RavEngine::PointLight>();
		light.SetIntensity(cc.radius * 1.3);
		light.SetColorRGBA({RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),1});
		mat->SetAlbedoColor(light.GetColorRGBA());
	}
};
