#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/System.hpp>

struct SpinComponent : public RavEngine::Component, public RavEngine::Queryable<SpinComponent>{
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};

struct SpinSystem : public RavEngine::AutoCTTI {
	bool paused = false;
	
    void Tick(float fpsScale,Ref<SpinComponent> c) {
		//get the entity and spin it based on the component data
        auto e = c->getOwner().lock();
        if (!paused && e){
            e->transform()->LocalRotateDelta((double)fpsScale * c->spinamt);
        }
	}
};
