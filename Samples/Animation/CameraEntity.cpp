#include "CameraEntity.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

using namespace RavEngine;
using namespace std;


void CameraScript::Tick(float fpsScale) {
	// where is the player? we should accelerate towards this position
	auto& targetTransform = target.GetTransform();
	auto& thisTransform = GetOwner().GetTransform();
    auto newPos = glm::mix(thisTransform.GetWorldPosition(), targetTransform.GetWorldPosition(), std::clamp<float>(0.3f * fpsScale,0,1));
    thisTransform.SetWorldPosition(newPos);
		
	// which way is the player facing? we want to rotate to be behind them
	auto facingRot = glm::quatLookAt(targetTransform.WorldForward(), thisTransform.WorldUp());
	thisTransform.SetWorldRotation(Slerp(thisTransform.GetWorldRotation(), facingRot, std::clamp<float>(0.01 * fpsScale,0,1)));
		
	// which way is the player moving? we want to swivel to a point ahead of them so they can see more easily
		
	// lastly, move the player by combining the input vectors
	auto combined = glm::normalize(forwardVector + rightVector);
	forwardVector = rightVector = vector3(0,0,0);
	if ((!std::isnan(combined.x) && !std::isnan(combined.y) && !std::isnan(combined.z)) && (glm::length(combined) > 0.3)){
		target.Move(combined,speedIncrement);
	}
}


void CameraEntity::Create(Character cm){
    GameObject::Create();
	// tip node with the camera, used for height-adjust and x-axis swivel
	cameraEntity = GetWorld()->Instantiate<GameObject>();
	auto& cam = cameraEntity.EmplaceComponent<CameraComponent>();
	cam.SetActive(true);
	
	// midway arm node used for distance-adjust and y-axis swivel
    cameraArmBase = GetWorld()->Instantiate<GameObject>();
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

void CameraEntity::Jump()
{
	cameraScript->target.Jump();
}

void CameraEntity::Pound()
{
	cameraScript->target.Pound();
}

void CameraScriptRunner::operator()(CameraScript& script)
{
	const auto fpsScale = GetApp()->GetCurrentFPSScale();
	script.Tick(fpsScale);
}
