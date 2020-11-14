//
//  WorldTest.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#include "WorldTest.hpp"
#include "RavEngine/System.hpp"
#include "SkateSystem.h"
#include "TestEntity.hpp"
#include "RavEngine/PhysicsLinkSystem.hpp"
#include "RavEngine/PhysicsBodyComponent.hpp"
#include "RavEngine/StaticMesh.hpp"
#include "RavEngine/PhysicsMaterial.hpp"
#include "RavEngine/ScriptSystem.hpp"
#include "RavEngine/BuiltinMaterials.hpp"
#include "RavEngine/InputManager.hpp"
#include <bgfx/bgfx.h>

using namespace RavEngine;
using namespace std;
Ref<RavEngine::Entity> anonymous;
Ref<RavEngine::Entity> anonymousChild;
Ref<RavEngine::Entity> floorplane;

void TestWorld::SpawnEntities(float f) {
    if (f > 0.99) {
		Ref<TestEntity> e = new TestEntity();
		Spawn(e);
    }
}

void TestWorld::ResetCam() {
	player->transform()->SetWorldPosition(vector3(0, -10, 50));
	player->transform()->SetWorldRotation(quaternion());
}

void TestWorld::posttick(float fpsScale){
    auto rotation = quaternion(vector3(0, 0, 0.01 * fpsScale));
    anonymous->transform()->LocalRotateDelta(rotation);
    scale = fpsScale;

    bgfx::dbgTextPrintf(0, 1, 0x4f, "FPS: %f", round(App::evalNormal/fpsScale));
    bgfx::dbgTextPrintf(0, 2, 0x4f, "FPS Scale: %lf", fpsScale);
    bgfx::dbgTextPrintf(0, 3, 0x4f, "Physics Bodies: %d", TestEntityController::objectcount.load());
}

TestWorld::TestWorld() : World() {

	//setup inputs
	Ref<RavEngine::InputManager> is = new RavEngine::InputManager();
	//setup control mappings
	is->AddAxisMap("MoveForward", SDL_SCANCODE_W);
	is->AddAxisMap("MoveForward", SDL_SCANCODE_S, -1);  //go backwards
	is->AddAxisMap("MoveRight", SDL_SCANCODE_A, -1);    //go left
	is->AddAxisMap("MoveRight", SDL_SCANCODE_D);        //turn left
	is->AddAxisMap("MoveUp", SDL_SCANCODE_SPACE);
	is->AddAxisMap("MoveUp", SDL_SCANCODE_LSHIFT, -1);
	is->AddAxisMap("LookUp", Special::MOUSEMOVE_YVEL,-1);   //turn up
	is->AddAxisMap("LookRight", Special::MOUSEMOVE_XVEL,-1);
	is->AddAxisMap("SpawnTest", SDL_SCANCODE_G);		//press g to spawn objects
	is->AddActionMap("ResetCam", SDL_SCANCODE_R);
	is->AddActionMap("SampleFPS",SDL_SCANCODE_T);

    //game controller input
    is->AddAxisMap("MoveForward", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY, -1);
    is->AddAxisMap("MoveRight", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
    is->AddAxisMap("LookRight", ControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX, -10);
    is->AddAxisMap("LookUp", ControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY, -10);
    is->AddAxisMap("MoveUp", ControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    is->AddAxisMap("MoveUp", ControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT,-1);
    is->AddAxisMap("SpawnTest", ControllerButton::SDL_CONTROLLER_BUTTON_A);
    is->AddActionMap("ResetCam", ControllerButton::SDL_CONTROLLER_BUTTON_START);
    is->AddActionMap("SampleFPS", ControllerButton::SDL_CONTROLLER_BUTTON_Y);

	auto con = CID::ANY;

	//bind controls
    auto playerscript = player->Components().GetComponent<PlayerScript>().get();
	is->BindAxis("MoveForward", playerscript, &PlayerScript::MoveForward,con);
	is->BindAxis("MoveRight", playerscript, &PlayerScript::MoveRight,con);
	is->BindAxis("MoveUp", playerscript,&PlayerScript::MoveUp,con);
	is->BindAxis("LookUp", playerscript,&PlayerScript::LookUp,con);
	is->BindAxis("LookRight", playerscript, &PlayerScript::LookRight,con);
	
	is->BindAxis("SpawnTest", this, &TestWorld::SpawnEntities,con);
	is->BindAction("ResetCam", this, &TestWorld::ResetCam, ActionState::Pressed,con);
	
    //test unbinding
	is->UnbindAxis("SpawnTest", this, &TestWorld::SpawnEntities,con);
	is->UnbindAction("ResetCam", this, &TestWorld::ResetCam, ActionState::Pressed,con);

    is->BindAxis("SpawnTest", this, &TestWorld::SpawnEntities,con);
    is->BindAction("ResetCam", this, &TestWorld::ResetCam, ActionState::Pressed,con);
	is->BindAction("SampleFPS",this, &TestWorld::SampleFPS,ActionState::Pressed,con);
	//is->BindAction("Click", click, ActionState::Released);
	RavEngine::App::inputManager = is;
	InputManager::SetRelativeMouseMode(true);
	
    //spawn player (it will make its camera active)
    Spawn(player);
	ResetCam();
	
    Ref<DefaultMaterialInstance> material = new DefaultMaterialInstance(Material::Manager::AccessMaterialOfType<DefaultMaterial>());

    Ref<MeshAsset> sharedMesh = new MeshAsset("cube.obj");

    anonymous = new RavEngine::Entity();
    anonymous->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);
    Spawn(anonymous);
    anonymous->transform()->LocalTranslateDelta(vector3(0, 1, 0));

    anonymousChild = new RavEngine::Entity();
    anonymousChild->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);;
    anonymous->transform()->AddChild(anonymousChild->transform());
    anonymousChild->transform()->LocalTranslateDelta(vector3(3,0,0));
    Spawn(anonymousChild);

    //register the systems that are allowed to run in this World
    //RegisterSystem(Ref<Skate>(new Skate()));

    InitPhysics();

    floorplane = new RavEngine::Entity();
    floorplane->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);
    floorplane->transform()->LocalScaleDelta(vector3(10, 0.5, 10));
    floorplane->transform()->LocalTranslateDelta(vector3(0, -20, 0));
    floorplane->AddComponent<RigidBodyStaticComponent>(new RigidBodyStaticComponent());
    floorplane->AddComponent<BoxCollider>(new BoxCollider(vector3(10, 1, 10), new PhysicsMaterial(0.5,0.5,0.5)));
    Spawn(floorplane);
};
