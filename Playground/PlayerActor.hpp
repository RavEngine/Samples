#pragma once
#include "RavEngine/Entity.hpp"
#include "RavEngine/CameraComponent.hpp"
#include "RavEngine/IInputListener.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include "RavEngine/ChildEntityComponent.hpp"
#include <algorithm>

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
		transform()->LocalTranslateDelta(scaleMovement(amt) * transform()->Forward());
	}
	void MoveRight(float amt) {
		transform()->LocalTranslateDelta(scaleMovement(amt) * transform()->Right());
	}

	void MoveUp(float amt) {
		transform()->LocalTranslateDelta(scaleMovement(amt) * transform()->Up());
	}

	void LookUp(float amt) {
		cameraEntity->transform()->LocalRotateDelta(vector3(scaleRotation(amt), 0, 0));
	}
	void LookRight(float amt) {
		transform()->LocalRotateDelta(quaternion(vector3(0, scaleRotation(amt), 0)));
	}

	virtual void Tick(float scale) override{
		dt = scale;
		//prevent camera from flipping over
		vector3 rotation = glm::eulerAngles(cameraEntity->transform()->GetLocalRotation());
		rotation.x = std::clamp(rotation.x, -RavEngine::PI/2.0, RavEngine::PI /2.0);
		cameraEntity->transform()->SetLocalRotation(rotation);
	}
};

class PlayerActor : public RavEngine::Entity, public RavEngine::IInputListener {
public:
	Ref<PlayerScript> script;
	PlayerActor() : Entity() {
		script = AddComponent<PlayerScript>(std::make_shared<PlayerScript>());
		
		//create a child entity for the camera
		auto cameraEntity = std::make_shared<Entity>();
		auto cam = cameraEntity->AddComponent<RavEngine::CameraComponent>(std::make_shared<RavEngine::CameraComponent>());
		script->cameraEntity = cameraEntity;
		
		//set the active camera
		cam->setActive(true);
		
		transform()->AddChild(cameraEntity->transform());
		AddComponent<RavEngine::ChildEntityComponent>(std::make_shared<RavEngine::ChildEntityComponent>(cameraEntity));
	}

	virtual ~PlayerActor(){}
};
