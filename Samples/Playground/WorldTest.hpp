//
//  WorldTest.hpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. 
//

#pragma once

#include "RavEngine/World.hpp"
#include "PlayerActor.hpp"
#include "RavEngine/IInputListener.hpp"
#include "RavEngine/App.hpp"
#include "RavEngine/Debug.hpp"

class TestWorld : public RavEngine::World{
public:
    void PostTick(float fpsScale) override;
    PlayerActor player;

	void ResetCam();
	void SpawnEntities(float);
	
	TestWorld();

    void SampleFPS() {
		RavEngine::Debug::Log("TPS: {}", RavEngine::GetApp()->CurrentTPS());
    }
protected: 
       float scale = 1;
};
