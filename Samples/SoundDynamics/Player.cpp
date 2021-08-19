#include "Player.hpp"
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>

using namespace RavEngine;
using namespace std;

Player::Player() {
	// camera
	auto camera = EmplaceComponent<CameraComponent>();
	camera->SetActive(true);

	// static rigid body
	auto body = EmplaceComponent<RigidBodyStaticComponent>();

	auto physicsMaterial = make_shared<PhysicsMaterial>(0,0,0);
	auto sphere = EmplaceComponent<SphereCollider>(1,physicsMaterial);

}