#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

struct Player : public RavEngine::ComponentWithOwner{
    
    Player(entity_t owner) : ComponentWithOwner(owner){}
	float zoomspeed = 1;

	float fpsScale = 0;
		
	void Zoom(float amt){
		auto zoomAmt = amt * zoomspeed;
        auto child = GetOwner().GetTransform().GetChildren()[0];
		child->LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child->Forward());
	}
	void RotateLR(float amt){
		GetOwner().GetTransform().LocalRotateDelta((double)fpsScale * vector3(0, glm::radians(amt), 0));
	}
	
	void RotateUD(float amt){
		GetOwner().GetTransform().LocalRotateDelta((double)fpsScale * vector3(glm::radians(amt), 0, 0));
	}
	
	void Tick(float scale){
		fpsScale = scale;
	}
};

struct PlayerSystem{
    inline void operator()(float fpsScale, Player& player) const{
        player.Tick(fpsScale);
    }
};

struct Camera : public RavEngine::GameObject{
	void Create(){
        GameObject::Create();
        auto cameraBoom = GetWorld()->CreatePrototype<GameObject>();
		
        EmplaceComponent<Player>();
		
		cameraBoom.GetTransform().LocalTranslateDelta(vector3(0,0,50));
		GetTransform().AddChild(RavEngine::ComponentHandle<RavEngine::Transform>(cameraBoom));
		
		auto& camera = cameraBoom.EmplaceComponent<RavEngine::CameraComponent>();
		camera.SetActive(true);
		camera.farClip = 500;
	}
};

