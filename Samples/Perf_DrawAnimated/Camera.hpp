#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/App.hpp>

struct Player : public RavEngine::ComponentWithOwner{
    
    Player(RavEngine::Entity owner) : ComponentWithOwner(owner){}
	float zoomspeed = 1;

	float fpsScale = 0;
		
	void Zoom(float amt){
		auto zoomAmt = amt * zoomspeed;
        auto child = GetOwner().GetTransform().GetChildren()[0];
		child->LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child->Forward());
	}
	void RotateLR(float amt){
		GetOwner().GetTransform().LocalRotateDelta((decimalType)fpsScale * vector3(0, deg_to_rad(amt), 0));
	}
	
	void RotateUD(float amt){
		GetOwner().GetTransform().LocalRotateDelta((decimalType)fpsScale * vector3(deg_to_rad(amt), 0, 0));
	}
	
	void Tick(float scale){
		fpsScale = scale;
	}
};

struct PlayerSystem{
    inline void operator()(Player& player) const{
        auto fpsScale = RavEngine::GetApp()->GetCurrentFPSScale();
        player.Tick(fpsScale);
    }
};

struct Camera : public RavEngine::GameObject{
	void Create(){
        GameObject::Create();
        auto cameraBoom = GetWorld()->Instantiate<GameObject>();
		
        EmplaceComponent<Player>();
		
		cameraBoom.GetTransform().LocalTranslateDelta(vector3(0,0,50));
		GetTransform().AddChild(RavEngine::ComponentHandle<RavEngine::Transform>(cameraBoom));
		
		auto& camera = cameraBoom.EmplaceComponent<RavEngine::CameraComponent>();
		camera.SetActive(true);
		camera.farClip = 500;
	}
};

