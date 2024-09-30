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
    Player(RavEngine::Entity id) : ComponentWithOwner(id){}
	void MoveUpDown(float amt);
	
	void MoveLeftRight(float amt);
};

class BotPlayer : public RavEngine::ScriptComponent{
protected:
    RavEngine::ComponentHandle<Player> pl;
	bool leftSide;
public:
	BotPlayer(RavEngine::Entity owner, decltype(pl) p, bool leftSide) : pl(p), leftSide(leftSide), ScriptComponent(owner){}
	
	void Tick(float scale) override;
};
