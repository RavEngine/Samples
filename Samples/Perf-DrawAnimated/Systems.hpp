#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/System.hpp>
#include <RavEngine/QueryIterator.hpp>

struct SpinComponent : public RavEngine::Component, public RavEngine::Queryable<SpinComponent>{
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};

struct SpinSystem : public RavEngine::AutoCTTI {
	bool paused = false;
	
	constexpr RavEngine::QueryIteratorAND<SpinComponent> QueryTypes() const {
		return RavEngine::QueryIteratorAND<SpinComponent>();
	}
	
    void Tick(float fpsScale, RavEngine::AccessRead<SpinComponent> c) {
		//get the entity and spin it based on the component data
        auto e = c.get()->getOwner().lock();
        if (!paused && e){
            e->transform()->LocalRotateDelta((double)fpsScale * c.get()->spinamt);
        }
	}
};
