#pragma once

#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/Utilities.hpp>
#include <atomic>

struct SineComponent: public RavEngine::AutoCTTI {
	float value = RavEngine::Random::get(-1.0,1.0); //ensure not every instance runs the same operations
};

struct CosComponent: public RavEngine::AutoCTTI {
	float value = RavEngine::Random::get(-1.0, 1.0);
};

struct CalcSystem : public RavEngine::AutoCTTI {
	inline void operator()(float fpsScale, SineComponent& sinecomp, CosComponent& coscomp) const{
		sinecomp.value = std::sin(sinecomp.value + fpsScale);
		coscomp.value = std::cos(coscomp.value + fpsScale);
	}
};

struct PA_Entity : public RavEngine::Entity {
	static std::atomic<uint16_t> num_objects;
	void Create() {
		EmplaceComponent<SineComponent>();
		EmplaceComponent<CosComponent>();
		num_objects++;
	}
};
