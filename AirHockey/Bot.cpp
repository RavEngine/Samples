#include "Player.hpp"
#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include <RavEngine/Debug.hpp>

using namespace std;
using namespace RavEngine;


void BotPlayer::Tick(float scale){
	//get all the pucks
	auto pucks = world->GetAllComponentsOfTypeFastPath<PuckComponent>();
	
	//define the goal position
	vector3 goalpos(0,0, leftSide? 3 : -3);

	//find the closest puck to the goal
	
	Ref<Entity> closestPuck = (*pucks.begin())->getOwner();
	auto worldpos = Ref<Entity>(getOwner())->transform()->GetWorldPosition();
	float closestDist = 1000;
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
	
	bool shouldChase = (!leftSide && pos.z < 0) || (leftSide && pos.z >= 0);
	
	vector3 dir;
	if (shouldChase){
		dir = glm::normalize(pos - worldpos);
	}
	else{
		//otherwise, move towards the puck's goal to guard it
		dir = glm::normalize(goalpos - worldpos);
	}
	
	pl->dir = dir;
}
