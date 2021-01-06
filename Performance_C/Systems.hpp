#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/System.hpp>

struct SpinComponent : public RavEngine::Component, public RavEngine::Queryable<SpinComponent>{
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};

struct SpinSystem : public RavEngine::System{
	bool paused = false;
	
	plf::list<RavEngine::ctti_t> QueryTypes() const override{
		return {RavEngine::CTTI<SpinComponent>};
	}
	
	void Tick(float fpsScale, Ref<RavEngine::Entity> e) const override{
		//get the entity and spin it based on the component data
		if (!paused){
			e->transform()->LocalRotateDelta((double)fpsScale * e->GetComponent<SpinComponent>()->spinamt);
		}
	}
};
