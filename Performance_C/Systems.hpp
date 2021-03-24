#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/System.hpp>

struct SpinComponent : public RavEngine::Component, public RavEngine::Queryable<SpinComponent>{
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};

struct SpinSystem {
	bool paused = false;
	
	const RavEngine::System::list_type& QueryTypes() const {
		return queries;
	}
	
    void Tick(float fpsScale, Ref<RavEngine::Component> c, RavEngine::ctti_t id) {
		//get the entity and spin it based on the component data
        auto e = c->getOwner().lock();
        if (!paused && e){
            e->transform()->LocalRotateDelta((double)fpsScale * std::static_pointer_cast<SpinComponent>(c)->spinamt);
        }
	}
protected:
	static const RavEngine::System::list_type queries;
};
