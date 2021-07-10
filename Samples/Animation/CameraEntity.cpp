#include "CameraEntity.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/ChildEntityComponent.hpp>

using namespace RavEngine;
using namespace std;

struct CameraScript : public RavEngine::ScriptComponent {
	Ref<Character> target;
	vector3 forwardVector = vector3(0,0,0);
	vector3 rightVector = vector3(0,0,0);
	decimalType speedIncrement = 1;
	
	CameraScript(const decltype(target)& t) : target(t){}
	
	void Tick(float fpsScale) final{
		// where is the player? we should accelerate towards this position
		auto targetTransform = target->transform();
		auto thisTransform = transform();
		auto dirvec = (thisTransform->GetWorldPosition() - targetTransform->GetWorldPosition()) * static_cast<double>(fpsScale) * -1.0;
		
		// if we are close, we should decelerate / accelerate smoothly
		if (glm::length(dirvec) > 4){
			dirvec = glm::normalize(dirvec) * 4.0;
		}
		thisTransform->WorldTranslateDelta(dirvec);
		
		// which way is the player facing? we want to rotate to be behind them
		
		// which way is the player moving? we want to swivel to a point ahead of them so they can see more easily
		
		// lastly, move the player by combining the input vectors
		auto combined = glm::normalize(forwardVector + rightVector);
		forwardVector = rightVector = vector3(0,0,0);
		if ((!std::isnan(combined.x) && !std::isnan(combined.y) && !std::isnan(combined.z)) && (glm::length(combined) > 0.3)){
			target->Move(combined,speedIncrement);
		}
	}
};

CameraEntity::CameraEntity(Ref<Character> cm){
	
	// tip node with the camera, used for height-adjust and x-axis swivel
	cameraEntity = make_shared<Entity>();
	cameraEntity->EmplaceComponent<CameraComponent>()->setActive(true);
	
	// midway arm node used for distance-adjust and y-axis swivel
	cameraArmBase = make_shared<Entity>();
	cameraArmBase->transform()->AddChild(cameraEntity->transform());
	cameraArmBase->EmplaceComponent<ChildEntityComponent>(cameraEntity);
	cameraEntity->transform()->LocalTranslateDelta(vector3(0,3,0));
	cameraEntity->transform()->LocalRotateDelta(vector3(glm::radians(-10.0),0,0));
	
	// attached to the root transform
	EmplaceComponent<ChildEntityComponent>(cameraArmBase);
	transform()->AddChild(cameraArmBase->transform());
	cameraArmBase->transform()->LocalTranslateDelta(vector3(0,0,7));
	
	cameraScript = EmplaceComponent<CameraScript>(cm);
}

void CameraEntity::MoveForward(float amt){
	// what is the camera's direction vector? movement is relative to the camera,
	// so up on the control stick is torwards the top of the screen rather than
	// the direction the character is facing.
	auto forward = cameraArmBase->transform()->WorldForward() * static_cast<decimalType>(amt);
	cameraScript->forwardVector += forward;
}

void CameraEntity::MoveRight(float amt){
	auto right = cameraArmBase->transform()->WorldRight() * static_cast<decimalType>(amt);
	cameraScript->rightVector += right;
}

void CameraEntity::SpeedIncrement(float s)
{
	cameraScript->speedIncrement = 1 + s;
}
