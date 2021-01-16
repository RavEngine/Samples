#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

struct Player : public RavEngine::ScriptComponent{
	
	float zoomspeed = 0.5;
	
	float zoomAmt = 0;
	vector3 rotateAmt;
	
	void Zoom(float amt){
		zoomAmt = amt * zoomspeed;
	}
	void RotateLR(float amt){
		rotateAmt.y = glm::radians(amt);
	}
	
	void RotateUD(float amt){
		rotateAmt.x = glm::radians(amt);
	}
	
	void Tick(float fpsScale) override{
		auto owner = Ref<RavEngine::Entity>(getOwner());
		auto transform = owner->transform();;
		transform->LocalRotateDelta((double)fpsScale * rotateAmt);
		
		auto child = owner->GetComponent<RavEngine::ChildEntityComponent>()->get()->transform();
		child->LocalTranslateDelta(vector3(0,0,zoomAmt * fpsScale) * child->Forward());
		
		zoomAmt = 0;
		rotateAmt.x = 0;
		rotateAmt.y = 0;
	}
	
};

struct Camera : public RavEngine::Entity{
	Camera(){
		
		Ref<Entity> cameraBoom = std::make_shared<Entity>();
		
		AddComponent<RavEngine::ChildEntityComponent>(std::make_shared<RavEngine::ChildEntityComponent>(cameraBoom));
		AddComponent<Player>(std::make_shared<Player>());
		
		cameraBoom->transform()->LocalTranslateDelta(vector3(0,0,50));
		transform()->AddChild(cameraBoom->transform());
		
		auto camera = cameraBoom->AddComponent<RavEngine::CameraComponent>(std::make_shared<RavEngine::CameraComponent>());
		camera->setActive(true);
		camera->farClip = 500;
	}
};

