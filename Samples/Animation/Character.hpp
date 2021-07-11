#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/DebugDraw.hpp>
#include <RavEngine/AnimatorComponent.hpp>

struct BoneDebugRenderer : public RavEngine::IDebugRenderer {
	void DrawDebug(RavEngine::DebugDraw& dbg) const override {
		auto owner = getOwner().lock();
		if (owner) {
			if (auto animator = owner->GetComponent<RavEngine::AnimatorComponent>()) {
				auto& pose = animator.value()->GetPose();
				for (const auto& p : pose) {
					dbg.DrawSphere(p, 0xFFFF00FF, 0.1);
				}
			}
		}
	}
};

struct CharacterScript;
struct Character : public RavEngine::Entity {
	Character();
	void Move(const vector3&, decimalType speedMultiplier = 0);
private:
	Ref<RavEngine::RigidBodyDynamicComponent> rigidBody;
	Ref<CharacterScript> script;
};
