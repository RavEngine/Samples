#pragma once

#include "Paddle.hpp"
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/IInputListener.hpp>
#include <RavEngine/Debug.hpp>

class Player : public RavEngine::Component, public RavEngine::Queryable<Player>{
protected:
	decimalType sensitivity = 15;
public:	
	void MoveUpDown(float amt){
		if (std::abs(amt) > 0.1){
			GetOwner().lock()->GetComponent<RavEngine::RigidBodyDynamicComponent>().value()->AddForce(vector3(amt,0,0) * sensitivity);
		}
	}
	
	void MoveLeftRight(float amt){
		if (std::abs(amt) > 0.1){
			GetOwner().lock()->GetComponent<RavEngine::RigidBodyDynamicComponent>().value()->AddForce(vector3(0,0,amt) * sensitivity);
		}
	}
};

class BotPlayer : public RavEngine::ScriptComponent{
protected:
	Ref<Player> pl;
	bool leftSide;
public:

	BotPlayer(Ref<Player> p, bool leftSide) : pl(p), leftSide(leftSide){}
	
	void Tick(float scale) override;
};
