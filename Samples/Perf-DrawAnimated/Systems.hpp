#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/Component.hpp>
#include <RavEngine/System.hpp>
#include <RavEngine/Transform.hpp>

struct SpinComponent : public RavEngine::AutoCTTI {
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};
