#pragma once

#include "Paddle.hpp"
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/IInputListener.hpp>

class Player : public RavEngine::ScriptComponent{
protected:
	decimalType sensitivity = 15;
public:
	vector3 dir;
	
	void MoveUpDown(float amt){
		dir.x = amt;
	}
	
	void MoveLeftRight(float amt){
		dir.z = amt;
	}
	
	virtual void Tick(float scale) override{
		if (glm::length(dir) > 0.1){
			GetEntity()->GetComponent<RavEngine::RigidBodyDynamicComponent>()->AddForce(glm::normalize(dir) * sensitivity * (decimalType)scale);
		}
		dir.x = dir.z = 0;
	}
};

class BotPlayer : public RavEngine::ScriptComponent{
protected:
	Ref<Player> pl;
	Ref<RavEngine::World> world;
public:

	BotPlayer(Ref<Player> p) : pl(p){}
	
	void Start() override{
		world = GetWorld();
	}
	
	void Tick(float scale) override;
};
