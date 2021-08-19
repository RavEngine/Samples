#include "Player.hpp"
#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include <RavEngine/Debug.hpp>

using namespace std;
using namespace RavEngine;


void BotPlayer::Tick(float scale){
	//get all the pucks
	auto pucks = GetWorld()->GetAllComponentsOfType<PuckComponent>();
	
	//define the goal position
	vector3 goalpos(0,0, leftSide? 3 : -3);

	//find the closest puck to the goal
	
	Ref<Entity> closestPuck(static_pointer_cast<PuckComponent>(*pucks.begin())->GetOwner());
	auto worldpos = Ref<Entity>(GetOwner())->GetTransform()->GetWorldPosition();
	float closestDist = 1000;
	for(auto puck : pucks){
        auto p = static_pointer_cast<PuckComponent>(puck);
		Ref<Entity> e(p->GetOwner());
		
		auto dist = glm::distance(e->GetTransform()->GetWorldPosition(), goalpos);
		if (dist <= closestDist){
			closestDist = dist;
			closestPuck = e;
		}
	}
	
	//if puck is on bot's side of the field, move towards that puck
	auto pos = closestPuck->GetTransform()->GetWorldPosition();
	
	bool shouldChase = (!leftSide && pos.z < 0) || (leftSide && pos.z >= 0);
	
	vector3 dir;
	if (shouldChase){
		dir = glm::normalize(pos - worldpos);
	}
	else{
		//otherwise, move towards the puck's goal to guard it
		dir = glm::normalize(goalpos - worldpos);
	}
	
	pl->MoveUpDown(dir.x);
	pl->MoveLeftRight(dir.z);
}
