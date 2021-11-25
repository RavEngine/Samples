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
    
    // anything that has these 2 calls
    // can be a target for input manager
    // however, the memory location of the
    // bound object must be stable
    inline auto get_id() const{
        return id;
    }
    
    inline Character* get() const{
        return const_cast<Character*>(this);
    }
    
private:
    RavEngine::ComponentHandle<RavEngine::RigidBodyDynamicComponent> rigidBody;
    RavEngine::ComponentHandle<CharacterScript> script;
};
