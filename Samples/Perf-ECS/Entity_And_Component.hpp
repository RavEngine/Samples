#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/Utilities.hpp>
#include <atomic>

struct SineComponent : public RavEngine::Component, public RavEngine::Queryable<SineComponent> {
	float value = RavEngine::Random::get(-1.0,1.0); //ensure not every instance runs the same operations
};

struct CosComponent : public RavEngine::Component, public RavEngine::Queryable<CosComponent> {
	float value = RavEngine::Random::get(-1.0, 1.0);
};

struct CalcSystem : public RavEngine::AutoCTTI {
	inline void Tick(float fpsScale, Ref<SineComponent> sinecomp, Ref<CosComponent> coscomp) {
		sinecomp->value = std::sin(sinecomp->value + fpsScale);
		coscomp->value = std::cos(coscomp->value + fpsScale);
	}
};

struct PA_Entity : public RavEngine::Entity {
	static std::atomic<uint16_t> num_objects;
	PA_Entity() {
		EmplaceComponent<SineComponent>();
		EmplaceComponent<CosComponent>();
		num_objects++;
	}
	~PA_Entity() {
		num_objects--;
	}
};
