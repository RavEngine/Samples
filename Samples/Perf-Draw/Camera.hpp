#pragma once
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>

struct Player : public RavEngine::ComponentWithOwner {
    
    Player(entity_t owner) : ComponentWithOwner(owner){}
    
	float zoomspeed = 1;

	float fpsScale = 0;

	void Zoom(float amt) {
		auto zoomAmt = amt * zoomspeed;
		auto& child = GetOwner().GetTransform().GetChildren()[0].GetOwner().GetTransform();
		child.LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child.Forward());
	}
	void RotateLR(float amt) {
		GetOwner().GetTransform().LocalRotateDelta((decimalType)fpsScale * vector3(0, deg_to_rad(amt), 0));
	}

	void RotateUD(float amt) {
		GetOwner().GetTransform().LocalRotateDelta((decimalType)fpsScale * vector3(deg_to_rad(amt), 0, 0));
	}

	void Tick(float scale) {
		fpsScale = scale;
	}
};

struct PlayerSystem{
    inline void operator()(float scale, Player& p) const{
        p.Tick(scale);
    }
};

struct Camera : public RavEngine::GameObject {
    void Create() {
        RavEngine::GameObject::Create();

		auto cameraBoom = GetWorld()->CreatePrototype<GameObject>();

		EmplaceComponent<Player>();

        auto& ctr = cameraBoom.GetTransform();
		ctr.LocalTranslateDelta(vector3(0, 0, 150));
        GetTransform().AddChild(cameraBoom);

		auto& camera = cameraBoom.EmplaceComponent<RavEngine::CameraComponent>();
		camera.SetActive(true);
		camera.farClip = 800;
	}
};

