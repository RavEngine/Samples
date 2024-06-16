#pragma once
#include <RavEngine/Queryable.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/GameObject.hpp>

namespace RavEngine {
	struct MeshCollectionStatic;
}

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
	void Create(Ref<RavEngine::MeshCollectionStatic> mesh);
};
