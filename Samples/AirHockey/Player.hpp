#pragma once

#include "Paddle.hpp"
#include <RavEngine/ComponentWithOwner.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/IInputListener.hpp>
#include <RavEngine/Debug.hpp>

class Player : public RavEngine::ComponentWithOwner, public RavEngine::Queryable<Player>{
protected:
	decimalType sensitivity = 15;
public:
    Player(entity_t id) : ComponentWithOwner(id){}
	void MoveUpDown(float amt){
		if (std::abs(amt) > 0.1){
			GetOwner().GetComponent<RavEngine::RigidBodyDynamicComponent>().AddForce(vector3(amt,0,0) * sensitivity);
		}
	}
	
	void MoveLeftRight(float amt){
		if (std::abs(amt) > 0.1){
			GetOwner().GetComponent<RavEngine::RigidBodyDynamicComponent>().AddForce(vector3(0,0,amt) * sensitivity);
		}
	}
};

class BotPlayer : public RavEngine::ScriptComponent{
protected:
    RavEngine::ComponentHandle<Player> pl;
	bool leftSide;
public:
	BotPlayer(entity_t owner, decltype(pl) p, bool leftSide) : pl(p), leftSide(leftSide), ScriptComponent(owner){}
	
	void Tick(float scale) override;
};
