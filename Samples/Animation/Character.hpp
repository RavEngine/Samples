#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/AnimatorComponent.hpp>

namespace RavEngine{
    struct RigidBodyDynamicComponent;
}

struct CharacterScript;
struct Character : public RavEngine::GameObject {
	void Create();
	void Move(const vector3&, decimalType speedMultiplier = 0);
	void Jump();
	void Pound();
private:
    RavEngine::ComponentHandle<RavEngine::RigidBodyDynamicComponent> rigidBody;
    RavEngine::ComponentHandle<CharacterScript> script;
};
