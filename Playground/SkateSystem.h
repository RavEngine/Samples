//
//  SkateSystem.h
//  MacFramework
//
//  Copyright © 2020 Ravbug.
//

#pragma once
#include <RavEngine/System.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/CTTI.hpp>
/**
 This system simply moves an entity along one axis
 */
class Skate : public RavEngine::System{
public:
    virtual ~Skate(){}
    
    virtual void Tick(float fpsScale, Ref<RavEngine::Entity> e) override{
        auto newPos = e->transform()->GetLocalPosition();
        newPos += 5 * fpsScale;
        e->transform()->SetLocalPosition(newPos);
    }

	plf::list<RavEngine::ctti_t> QueryTypes() const override {
		return { RavEngine::CTTI<RavEngine::Transform> };
    }
};
