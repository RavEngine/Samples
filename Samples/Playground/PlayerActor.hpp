#pragma once
#include "RavEngine/GameObject.hpp"
#include "RavEngine/CameraComponent.hpp"
#include "RavEngine/IInputListener.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/ComponentWithOwner.hpp>

class PlayerActor;
struct PlayerScript : public RavEngine::ScriptComponent, public RavEngine::IInputListener, public RavEngine::Queryable<PlayerScript,RavEngine::ScriptComponent> {
	using Queryable<PlayerScript, RavEngine::ScriptComponent>::GetQueryTypes;

    PlayerScript(entity_t owner) : ScriptComponent(owner){}
    
	RavEngine::Entity cameraEntity;
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
		auto& tn = GetOwner().GetTransform();
		tn.LocalTranslateDelta(scaleMovement(amt) * tn.Forward());
	}
	void MoveRight(float amt) {
		auto& tn = GetOwner().GetTransform();
		tn.LocalTranslateDelta(scaleMovement(amt) * tn.Right());
	}

	void MoveUp(float amt) {
		auto& tn = GetOwner().GetTransform();
       tn.LocalTranslateDelta(scaleMovement(amt) * tn.Up());
	}

	void LookUp(float amt) {
		cameraEntity.GetTransform().LocalRotateDelta(vector3(scaleRotation(amt), 0, 0));
	}
	void LookRight(float amt) {
        GetOwner().GetTransform().LocalRotateDelta(quaternion(vector3(0, scaleRotation(amt), 0)));
	}

    void Tick(float scale) override{
		dt = scale;
		//prevent camera from flipping over
		vector3 rotation = glm::eulerAngles(cameraEntity.GetTransform().GetLocalRotation());
		rotation.x = std::clamp(rotation.x, -RavEngine::PI/2.0, RavEngine::PI /2.0);
		cameraEntity.GetTransform().SetLocalRotation(rotation);
	}
};

class PlayerActor : public RavEngine::GameObject, public RavEngine::IInputListener {
public:
	RavEngine::ComponentHandle<PlayerScript> script;
	void Create() {
		GameObject::Create();
		EmplaceComponent<PlayerScript>();
		script = RavEngine::ComponentHandle<PlayerScript>(this);
		
		//create a child entity for the camera
		auto cameraEntity = GetWorld()->CreatePrototype<RavEngine::GameObject>();
		auto& cam = cameraEntity.EmplaceComponent<RavEngine::CameraComponent>();
		script->cameraEntity = cameraEntity;
		
		//set the active camera
		cam.SetActive(true);
		
		GetTransform().AddChild(RavEngine::ComponentHandle<RavEngine::Transform>(cameraEntity));
		
		EmplaceComponent<RavEngine::AudioListener>();
	}
};
