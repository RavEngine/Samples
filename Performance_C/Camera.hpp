#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

struct Player : public RavEngine::ScriptComponent{
	float zoomspeed = 1;

	float fpsScale = 0;
		
	void Zoom(float amt){
		auto owner = Ref<RavEngine::Entity>(getOwner());
		auto zoomAmt = amt * zoomspeed;
		auto child = owner->GetComponent<RavEngine::ChildEntityComponent>().value()->get()->transform();
		child->LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child->Forward());
	}
	void RotateLR(float amt){
		auto owner = Ref<RavEngine::Entity>(getOwner());
		owner->transform()->LocalRotateDelta((double)fpsScale * vector3(0, glm::radians(amt), 0));
	}
	
	void RotateUD(float amt){
		auto owner = Ref<RavEngine::Entity>(getOwner());
		owner->transform()->LocalRotateDelta((double)fpsScale * vector3(glm::radians(amt), 0, 0));
	}
	
	void Tick(float scale) override{		
		fpsScale = scale;
	}
};

struct Camera : public RavEngine::Entity{
	Camera(){
		
		Ref<Entity> cameraBoom = std::make_shared<Entity>();
		
        EmplaceComponent<RavEngine::ChildEntityComponent>(cameraBoom);
        EmplaceComponent<Player>();
		
		cameraBoom->transform()->LocalTranslateDelta(vector3(0,0,50));
		transform()->AddChild(cameraBoom->transform());
		
		auto camera = cameraBoom->EmplaceComponent<RavEngine::CameraComponent>();
		camera->setActive(true);
		camera->farClip = 500;
	}
};

