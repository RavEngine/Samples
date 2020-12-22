#pragma once

#include "Paddle.hpp"
#include <RavEngine/IInputListener.hpp>
#include <cmath>

class Player : public RavEngine::ScriptComponent, public RavEngine::IInputListener{
protected:
	decimalType sensitivity = 15;
	vector3 dir;
public:
	
	void MoveUpDown(float amt){
		dir.x = amt;
	}
	
	void MoveLeftRight(float amt){
		dir.z = amt;
	}
	
	virtual void Tick(float scale) override{
		GetEntity()->Components().GetComponent<RigidBodyDynamicComponent>()->AddForce(glm::normalize(dir) * sensitivity * (decimalType)scale);
		dir.x = dir.z = 0;
	}
};
