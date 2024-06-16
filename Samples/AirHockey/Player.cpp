#include "Player.hpp"
#include <RavEngine/PhysicsBodyComponent.hpp>

using namespace RavEngine;

void Player::MoveUpDown(float amt)
{
	if (std::abs(amt) > 0.1) {
		GetOwner().GetComponent<RavEngine::RigidBodyDynamicComponent>().AddForce(vector3(amt, 0, 0) * sensitivity);
	}
}

void Player::MoveLeftRight(float amt)
{
	if (std::abs(amt) > 0.1) {
		GetOwner().GetComponent<RavEngine::RigidBodyDynamicComponent>().AddForce(vector3(0, 0, amt) * sensitivity);
	}
}
