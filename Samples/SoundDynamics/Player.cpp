#include "Player.hpp"
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

using namespace RavEngine;
using namespace std;

struct PlayerController : public RavEngine::ScriptComponent {
	decimalType scaleFactor = 0;
	decimalType movementSpeed = 0.1;
	decimalType rotationSpeed = 0.05;

	inline decimalType scale(decimalType amt) {
		return amt * scaleFactor * movementSpeed;
	}

	inline void MoveForward(decimalType amt) {
		auto tr = GetTransform();
		tr->LocalTranslateDelta(tr->Forward() * scale(amt));
	}

	inline void MoveRight(decimalType amt) {
		auto tr = GetTransform();
		tr->LocalTranslateDelta(tr->Right() * scale(amt));
	}

	inline void MoveUp(decimalType amt) {
		auto tr = GetTransform();
		tr->LocalTranslateDelta(tr->Up() * scale(amt));
	}

	inline void LookUp(decimalType amt) {
		auto tr = GetComponent<ChildEntityComponent>().value()->GetEntity()->GetTransform();
		tr->LocalRotateDelta(vector3(glm::radians(amt * rotationSpeed), 0, 0));
	}

	inline void LookRight(decimalType amt) {
		auto tr = GetTransform();
		tr->LocalRotateDelta(vector3(0, glm::radians(amt * rotationSpeed), 0));
	}

	void Tick(float scale) final {
		scaleFactor = scale;
	}
};

Player::Player() {
	auto cameraEntity = make_shared<Entity>();

	auto camera = cameraEntity->EmplaceComponent<CameraComponent>();
	camera->SetActive(true);

	// microphone / ear
	cameraEntity->EmplaceComponent<AudioListener>();

	// child entity w/ camera
	EmplaceComponent<ChildEntityComponent>(cameraEntity);

	// static rigid body
	auto body = EmplaceComponent<RigidBodyStaticComponent>();

	auto physicsMaterial = make_shared<PhysicsMaterial>(0,0,0);
	auto sphere = EmplaceComponent<SphereCollider>(1,physicsMaterial);

	GetTransform()->AddChild(cameraEntity->GetTransform());

	EmplaceComponent<PlayerController>();
}

void Player::MoveForward(float amt) {
	GetScript()->MoveForward(amt);
}

void Player::MoveRight(float amt) {
	GetScript()->MoveRight(amt);
}

void Player::MoveUp(float amt)
{
	GetScript()->MoveUp(amt);
}

void Player::LookRight(float amt) {
	GetScript()->LookRight(amt);
}

void Player::LookUp(float amt) {
	GetScript()->LookUp(amt);
}

Ref<PlayerController> Player::GetScript()
{
	return GetComponent<PlayerController>().value();
}