//
//  WorldTest.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug.
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
#include "RavEngine/Light.hpp"
#include <bgfx/bgfx.h>

using namespace RavEngine;
using namespace std;
static Ref<RavEngine::Entity> anonymous;
static Ref<RavEngine::Entity> anonymousChild;
static Ref<RavEngine::Entity> floorplane;
static Ref<Entity> ambientLight1;
static Ref<Entity> dl;
static int ct = 0;

float currentTime = 0;

void TestWorld::SpawnEntities(float f) {
    if (f > 0.99) {
		Ref<TestEntity> e = new TestEntity();
		Spawn(e);
    }
//	if (f > 0.99){
//		for(int i = 0; i < 8; i++){
//			Ref<Entity> e = new Entity();
//			Spawn(e);
//		}
//		TestEntityController::objectcount+=8;
//	}
}

void TestWorld::ResetCam() {
	player->transform()->SetWorldPosition(vector3(0, -10, 50));
	player->transform()->SetWorldRotation(quaternion());
}

void TestWorld::posttick(float fpsScale){
	currentTime += fpsScale;
    auto rotation = quaternion(vector3(0, 0, 0.01 * fpsScale));
    anonymous->transform()->LocalRotateDelta(rotation);
    scale = fpsScale;
	
    bgfx::dbgTextPrintf(0, 1, 0x4f, "FPS: %f", round(App::evalNormal/fpsScale));
    bgfx::dbgTextPrintf(0, 2, 0x4f, "FPS Scale: %lf", fpsScale);
    bgfx::dbgTextPrintf(0, 3, 0x4f, "Physics Bodies: %d", TestEntityController::objectcount.load());
	
	dl->transform()->LocalRotateDelta(vector3(0,0,glm::radians(1*fpsScale)));
	
	//floorplane->transform()->SetLocalPosition(anonymousChild->transform()->GetWorldPosition());
	
	//floorplane->transform()->SetLocalPosition(vector3(0,-20+sin(currentTime/50)*3,0));
	
	//anonymousChild->Components().GetComponent<PhysicsCollider>()->DebugDraw(0xFFFFFFFF);

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
	
    Ref<PBRMaterialInstance> material = new PBRMaterialInstance(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	
//	Ref<Texture> t = new Texture("youcantrun.png");
//	material->SetAlbedoTexture(t);

    Ref<MeshAsset> sharedMesh = new MeshAsset("cube.obj");

    anonymous = new RavEngine::Entity();
    anonymous->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);
    Spawn(anonymous);
    anonymous->transform()->LocalTranslateDelta(vector3(0, 1, 0));
	
	InitPhysics();

    anonymousChild = new RavEngine::Entity();
    anonymousChild->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);;
    anonymous->transform()->AddChild(anonymousChild->transform());
    anonymousChild->transform()->LocalTranslateDelta(vector3(17,0,0));
	anonymousChild->AddComponent<PointLight>(new PointLight())->Intensity = 4;
	anonymousChild->AddComponent<RigidBodyStaticComponent>(new RigidBodyStaticComponent());
	anonymousChild->AddComponent<BoxCollider>(new BoxCollider(vector3(1,1,1),new PhysicsMaterial(0.5,0.5,0.5)));
    Spawn(anonymousChild);

    //register the systems that are allowed to run in this World
    //RegisterSystem(Ref<Skate>(new Skate()));

    floorplane = new RavEngine::Entity();
    floorplane->AddComponent<StaticMesh>(new StaticMesh(sharedMesh))->SetMaterial(material);
    floorplane->transform()->LocalScaleDelta(vector3(10, 0.5, 10));
    floorplane->transform()->LocalTranslateDelta(vector3(0, -20, 0));
    floorplane->AddComponent<RigidBodyStaticComponent>(new RigidBodyStaticComponent());
    floorplane->AddComponent<BoxCollider>(new BoxCollider(vector3(10, 1, 10), new PhysicsMaterial(0.5,0.5,0.5)));
	anonymous->transform()->AddChild(floorplane->transform());
    Spawn(floorplane);
	
	dl = new Entity();
	auto dll = dl->AddComponent<DirectionalLight>(new DirectionalLight());
	auto amt = glm::radians(45.0);
	dl->transform()->LocalRotateDelta(vector3(amt,0,0));
	dl->transform()->LocalTranslateDelta(vector3(0,1,1));
	dll->color = {1,0.5,0};
	Spawn(dl);
	
	ambientLight1 = new Entity();
	auto light = ambientLight1->AddComponent<AmbientLight>(new AmbientLight());
	light->Intensity = 1;
	light->color = {0.1, 0.2, 0.4};
	Spawn(ambientLight1);
	
};
