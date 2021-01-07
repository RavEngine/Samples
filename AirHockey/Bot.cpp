#include "Player.hpp"
#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include <RavEngine/Debug.hpp>

using namespace std;
using namespace RavEngine;

void BotPlayer::Tick(float scale){
	//get all the pucks
	auto& pucks = world->GetAllComponentsOfTypeFastPath<PuckComponent>();
	
	//find the closest puck to the goal
	
	Ref<Entity> closestPuck = (*pucks.begin())->getOwner();
	float closestDist = 1000;
	
	constexpr vector3 goalpos(0,0,-3);
	
	for(Ref<PuckComponent> p : pucks){
		Ref<Entity> e = p->getOwner();
		
		auto dist = glm::distance(e->transform()->GetWorldPosition(), goalpos);
		if (dist <= closestDist){
			closestDist = dist;
			closestPuck = e;
		}
	}
	
	//if puck is on bot's side of the field, move towards that puck
	auto pos = closestPuck->transform()->GetWorldPosition();
	if (pos.z < 0){
		pl->dir = glm::normalize( pos - Ref<Entity>(getOwner())->transform()->GetWorldPosition() );
	}
	else{
		//otherwise, move towards the puck's goal to guard it
		pl->dir = glm::normalize( goalpos - Ref<Entity>(getOwner())->transform()->GetWorldPosition() );
	}
		
}
