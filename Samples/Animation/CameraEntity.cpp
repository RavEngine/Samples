#include "CameraEntity.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

using namespace RavEngine;
using namespace std;

struct CameraScript : public RavEngine::ScriptComponent {
	Character target;
	vector3 forwardVector = vector3(0,0,0);
	vector3 rightVector = vector3(0,0,0);
	decimalType speedIncrement = 0;
	
	CameraScript(entity_t owner, const decltype(target)& t) : target(t), ScriptComponent(owner){}
	
	void Tick(float fpsScale) final{
		// where is the player? we should accelerate towards this position
		auto& targetTransform = target.GetTransform();
		auto& thisTransform = GetTransform();
		auto dirvec = (thisTransform.GetWorldPosition() - targetTransform.GetWorldPosition()) * static_cast<decimalType>(fpsScale*  -1.f);
		
		// if we are close, we should decelerate / accelerate smoothly
		if (glm::length(dirvec) > 4){
			dirvec = glm::normalize(dirvec) * 4.f;
		}
		thisTransform.WorldTranslateDelta(dirvec);
		
		// which way is the player facing? we want to rotate to be behind them
		auto facingRot = glm::quatLookAt(targetTransform.WorldForward(), GetTransform().WorldUp());
		GetTransform().SetWorldRotation(Slerp(GetTransform().GetWorldRotation(), facingRot, 0.01 * fpsScale));
		
		// which way is the player moving? we want to swivel to a point ahead of them so they can see more easily
		
		// lastly, move the player by combining the input vectors
		auto combined = glm::normalize(forwardVector + rightVector);
		forwardVector = rightVector = vector3(0,0,0);
		if ((!std::isnan(combined.x) && !std::isnan(combined.y) && !std::isnan(combined.z)) && (glm::length(combined) > 0.3)){
			target.Move(combined,speedIncrement);
		}
	}
};

void CameraEntity::Create(Character cm){
    GameObject::Create();
	// tip node with the camera, used for height-adjust and x-axis swivel
	cameraEntity = GetWorld()->CreatePrototype<GameObject>();
	cameraEntity.EmplaceComponent<CameraComponent>().SetActive(true);
	
	// midway arm node used for distance-adjust and y-axis swivel
    cameraArmBase = GetWorld()->CreatePrototype<GameObject>();
	cameraArmBase.GetTransform().AddChild(cameraEntity);
	cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,3,0)).LocalRotateDelta(vector3(deg_to_rad(-10),0,0));
	
	// attached to the root transform
	GetTransform().AddChild(cameraArmBase);
	cameraArmBase.GetTransform().LocalTranslateDelta(vector3(0,0,7));
	
	EmplaceComponent<CameraScript>(cm);
    cameraScript = ComponentHandle<CameraScript>(this);
}

void CameraEntity::MoveForward(float amt){
	// what is the camera's direction vector? movement is relative to the camera,
	// so up on the control stick is torwards the top of the screen rather than
	// the direction the character is facing.
	auto forward = cameraArmBase.GetTransform().WorldForward() * static_cast<decimalType>(amt);
	cameraScript->forwardVector += forward;
}

void CameraEntity::MoveRight(float amt){
	auto right = cameraArmBase.GetTransform().WorldRight() * static_cast<decimalType>(amt);
	cameraScript->rightVector += right;
}

void CameraEntity::SpeedIncrement(float s)
{
	cameraScript->speedIncrement = s;
}
