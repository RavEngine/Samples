#pragma once
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/CameraComponent.hpp>

struct Player : public RavEngine::ScriptComponent {
	float zoomspeed = 1;

	float fpsScale = 0;

	void Zoom(float amt) {
		auto owner = Ref<RavEngine::Entity>(GetOwner());
		auto zoomAmt = amt * zoomspeed;
		auto child = owner->GetComponent<RavEngine::ChildEntityComponent>().value()->GetEntity()->Transform();
		child->LocalTranslateDelta(vector3(0, 0, zoomAmt * fpsScale) * child->Forward());
	}
	void RotateLR(float amt) {
		auto owner = Ref<RavEngine::Entity>(GetOwner());
		owner->Transform()->LocalRotateDelta((double)fpsScale * vector3(0, glm::radians(amt), 0));
	}

	void RotateUD(float amt) {
		auto owner = Ref<RavEngine::Entity>(GetOwner());
		owner->Transform()->LocalRotateDelta((double)fpsScale * vector3(glm::radians(amt), 0, 0));
	}

	void Tick(float scale) override {
		fpsScale = scale;
	}
};

struct Camera : public RavEngine::Entity {
	Camera() {

		Ref<Entity> cameraBoom = std::make_shared<Entity>();

		EmplaceComponent<RavEngine::ChildEntityComponent>(cameraBoom);
		EmplaceComponent<Player>();

		cameraBoom->Transform()->LocalTranslateDelta(vector3(0, 0, 50));
		Transform()->AddChild(cameraBoom->Transform());

		auto camera = cameraBoom->EmplaceComponent<RavEngine::CameraComponent>();
		camera->SetActive(true);
		camera->farClip = 500;
	}
};

