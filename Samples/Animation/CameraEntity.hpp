#pragma once
#include <RavEngine/GameObject.hpp>
#include "Character.hpp"

struct CameraScript : public RavEngine::ComponentWithOwner {
    Character target;
    vector3 forwardVector = vector3(0, 0, 0);
    vector3 rightVector = vector3(0, 0, 0);
    decimalType speedIncrement = 0;

    CameraScript(entity_t owner, const decltype(target)& t) : target(t), ComponentWithOwner(owner) {}
    void Tick(float);
};
struct CameraEntity : public RavEngine::GameObject {
	void Create(Character);

    // handling input manager events inside an entity handle is possible, but
    // not recommended
	void MoveForward(float);
	void MoveRight(float);
	void SpeedIncrement(float);
    
    inline auto get_id( )const{
        return id;
    }
    
    inline auto get(){
        return this;
    }
    
private:
	RavEngine::GameObject cameraEntity, cameraArmBase;
    RavEngine::ComponentHandle<CameraScript> cameraScript;
};

struct CameraScriptRunner : public RavEngine::AutoCTTI{
    void operator()(CameraScript&);
};
