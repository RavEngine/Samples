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

class TestWorld : public RavEngine::World{
public:
    void posttick(float fpsScale) override;
    TestWorld();
    Ref<PlayerActor> player = std::make_shared<PlayerActor>();

    virtual ~TestWorld() {

    }
	void ResetCam();
	void SpawnEntities(float);


    void SampleFPS() {
        std::cout << "FPS: " << RavEngine::App::evalNormal / scale << std::endl;
    }
protected: 
       float scale = 1;
};
