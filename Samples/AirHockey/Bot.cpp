#include "Player.hpp"
#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include <RavEngine/Debug.hpp>

using namespace std;
using namespace RavEngine;


void BotPlayer::Tick(float scale){
	//define the goal position
	vector3 goalpos(0,0, leftSide? 3 : -3);

	//find the closest puck to the goal
    Entity closestPuck = GetOwner().GetWorld()->GetComponent<PuckComponent>().GetOwner();
    auto worldpos = GetOwner().GetTransform().GetWorldPosition();
    float closestDist = 1000;
    

    GetOwner().GetWorld()->Filter([&](const PuckComponent& puck, const Transform& transform) mutable {
		auto dist = glm::distance(transform.GetWorldPosition(), goalpos);
		if (dist <= closestDist) {
			closestDist = dist;
			closestPuck = puck.GetOwner();
		}
	});

	//if puck is on bot's side of the field, move towards that puck
	auto pos = closestPuck.GetTransform().GetWorldPosition();
	
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
