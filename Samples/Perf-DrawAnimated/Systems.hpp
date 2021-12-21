#pragma once
#include <RavEngine/Common3D.hpp>

struct SpinComponent : public RavEngine::AutoCTTI {
	SpinComponent(const vector3& amt) : spinamt(amt){};
	vector3 spinamt;
};
