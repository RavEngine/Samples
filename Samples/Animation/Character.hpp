#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/AnimatorComponent.hpp>

struct CharacterScript;
struct Character : public RavEngine::Entity {
	Character();
	void Move(const vector3&, decimalType speedMultiplier = 0);
	void Jump();
	void Pound();
private:
	Ref<RavEngine::RigidBodyDynamicComponent> rigidBody;
	Ref<CharacterScript> script;
};
