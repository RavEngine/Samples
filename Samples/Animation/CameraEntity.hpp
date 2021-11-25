#pragma once
#include <RavEngine/GameObject.hpp>
#include "Character.hpp"

struct CameraScript;

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
