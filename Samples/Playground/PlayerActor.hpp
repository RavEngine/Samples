#pragma once
#include "RavEngine/Entity.hpp"
#include "RavEngine/CameraComponent.hpp"
#include "RavEngine/IInputListener.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include "RavEngine/ChildEntityComponent.hpp"
#include <RavEngine/AudioSource.hpp>

class PlayerActor;
class PlayerScript : public RavEngine::ScriptComponent, public RavEngine::IInputListener {
public:
	Ref<RavEngine::Entity> cameraEntity;
	decimalType dt = 0;
	decimalType movementSpeed = 0.3;
	decimalType sensitivity = 0.1;

	decimalType scaleMovement(decimalType f) {
		return f * dt * movementSpeed;
	}

	decimalType scaleRotation(decimalType f) {
		return glm::radians(sensitivity * dt * f);
	}

	void MoveForward(float amt) {
		GetTransform()->LocalTranslateDelta(scaleMovement(amt) * GetTransform()->Forward());
	}
	void MoveRight(float amt) {
		GetTransform()->LocalTranslateDelta(scaleMovement(amt) * GetTransform()->Right());
	}

	void MoveUp(float amt) {
		GetTransform()->LocalTranslateDelta(scaleMovement(amt) * GetTransform()->Up());
	}

	void LookUp(float amt) {
		cameraEntity->GetTransform()->LocalRotateDelta(vector3(scaleRotation(amt), 0, 0));
	}
	void LookRight(float amt) {
		GetTransform()->LocalRotateDelta(quaternion(vector3(0, scaleRotation(amt), 0)));
	}

	virtual void Tick(float scale) override{
		dt = scale;
		//prevent camera from flipping over
		vector3 rotation = glm::eulerAngles(cameraEntity->GetTransform()->GetLocalRotation());
		rotation.x = std::clamp(rotation.x, -RavEngine::PI/2.0, RavEngine::PI /2.0);
		cameraEntity->GetTransform()->SetLocalRotation(rotation);
	}
};

class PlayerActor : public RavEngine::Entity, public RavEngine::IInputListener {
public:
	Ref<PlayerScript> script;
	PlayerActor() : Entity() {
		script = EmplaceComponent<PlayerScript>();
		
		//create a child entity for the camera
		auto cameraEntity = std::make_shared<Entity>();
		auto cam = cameraEntity->EmplaceComponent<RavEngine::CameraComponent>();
		script->cameraEntity = cameraEntity;
		
		//set the active camera
		cam->SetActive(true);
		
		GetTransform()->AddChild(cameraEntity->GetTransform());
        EmplaceComponent<RavEngine::ChildEntityComponent>(cameraEntity);
		
		EmplaceComponent<RavEngine::AudioListener>();
	}

	virtual ~PlayerActor(){}
};
