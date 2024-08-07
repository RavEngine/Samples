#include "Player.hpp"
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/InputManager.hpp>

using namespace RavEngine;
using namespace std;

void Player::Create() {
    GameObject::Create();
	auto cameraEntity = GetWorld()->Instantiate<GameObject>();

	auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
	camera.SetActive(true);

	// microphone / ear
	cameraEntity.EmplaceComponent<AudioListener>();

	// child entity w/ camera

	// static rigid body
	auto& body = EmplaceComponent<RigidBodyStaticComponent>();

	auto physicsMaterial = RavEngine::New<PhysicsMaterial>(0,0,0);
	body.EmplaceCollider<SphereCollider>(1.f,physicsMaterial);

    ComponentHandle<Transform> ctr(cameraEntity);
	GetTransform().AddChild(ctr);

	auto& player = EmplaceComponent<PlayerController>();
    player.childTransform = ctr;
}
