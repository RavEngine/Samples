#pragma once
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/CameraComponent.hpp>

struct Player : public RavEngine::ComponentWithOwner {
    
    Player(entity_t owner) : ComponentWithOwner(owner){}
    
	float zoomspeed = 1;

	float fpsScale = 0;

	void Zoom(float amt) {
		auto zoomAmt = amt * zoomspeed;
		auto& child = GetOwner().GetComponent<RavEngine::ChildEntityComponent>().GetEntity().GetTransform();
		child.LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child.Forward());
	}
	void RotateLR(float amt) {
		GetOwner().GetTransform().LocalRotateDelta((double)fpsScale * vector3(0, glm::radians(amt), 0));
	}

	void RotateUD(float amt) {
		GetOwner().GetTransform().LocalRotateDelta((double)fpsScale * vector3(glm::radians(amt), 0, 0));
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

		EmplaceComponent<RavEngine::ChildEntityComponent>(cameraBoom);
		EmplaceComponent<Player>();

        auto& ctr = cameraBoom.GetTransform();
		ctr.LocalTranslateDelta(vector3(0, 0, 50));
        GetTransform().AddChild(RavEngine::ComponentHandle<RavEngine::Transform>(cameraBoom));

		auto& camera = cameraBoom.EmplaceComponent<RavEngine::CameraComponent>();
		camera.SetActive(true);
		camera.farClip = 500;
	}
};

