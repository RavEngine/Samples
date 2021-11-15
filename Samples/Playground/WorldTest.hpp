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
    TestWorld();
    PlayerActor player;

	void ResetCam();
	void SpawnEntities(float);
	
	/**
	 Because you can't call shared_from_this in a constructor, to bind inputs to functions on the World, you must
	 use an external function. See TestApp.h
	 */
	void SetupInputs();

    void SampleFPS() {
		RavEngine::Debug::Log("TPS: {}", RavEngine::App::CurrentTPS());
    }
protected: 
       float scale = 1;
};
