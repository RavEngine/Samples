//
//  WorldTest.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug.
//

#include "WorldTest.hpp"
#include "RavEngine/System.hpp"
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

void TestWorld::SpawnEntities(float f) {
    if (f > 0.99) {
		Ref<TestEntity> e = std::make_shared<TestEntity>();
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
    auto rotation = quaternion(vector3(0, 0, 0.01 * fpsScale));
    anonymous->transform()->LocalRotateDelta(rotation);
    scale = fpsScale;
	
    //bgfx::dbgTextPrintf(0, 1, 0x4f, "FPS: %f", round(App::evalNormal/fpsScale));
    //bgfx::dbgTextPrintf(0, 2, 0x4f, "FPS Scale: %lf", fpsScale);
    //bgfx::dbgTextPrintf(0, 3, 0x4f, "Physics Bodies: %d", TestEntityController::objectcount.load());
	
	dl->transform()->LocalRotateDelta(vector3(0,0,glm::radians(1*fpsScale)));
}

void TestWorld::SetupInputs(){
	//setup inputs
	Ref<RavEngine::InputManager> is = make_shared<RavEngine::InputManager>();
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
	auto playerscript = player->GetComponent<PlayerScript>();
	is->BindAxis("MoveForward", playerscript, &PlayerScript::MoveForward,con);
	is->BindAxis("MoveRight", playerscript, &PlayerScript::MoveRight,con);
	is->BindAxis("MoveUp", playerscript,&PlayerScript::MoveUp,con);
	is->BindAxis("LookUp", playerscript,&PlayerScript::LookUp,con);
	is->BindAxis("LookRight", playerscript, &PlayerScript::LookRight,con);
	
	auto ptr = std::static_pointer_cast<TestWorld>(shared_from_this());
	
	is->BindAxis("SpawnTest", ptr, &TestWorld::SpawnEntities,con);
	is->BindAction("ResetCam", ptr, &TestWorld::ResetCam, ActionState::Pressed,con);
	
	//test unbinding
	//	is->UnbindAxis("SpawnTest", std::static_pointer_cast<TestWorld>(shared_from_this()), &TestWorld::SpawnEntities,con);
	//	is->UnbindAction("ResetCam", std::static_pointer_cast<TestWorld>(shared_from_this()), &TestWorld::ResetCam, ActionState::Pressed,con);
	
	is->BindAxis("SpawnTest", ptr, &TestWorld::SpawnEntities,con);
	is->BindAction("ResetCam", ptr, &TestWorld::ResetCam, ActionState::Pressed,con);
	is->BindAction("SampleFPS",ptr, &TestWorld::SampleFPS,ActionState::Pressed,con);
	//is->BindAction("Click", click, ActionState::Released);
	RavEngine::App::inputManager = is;
	
	InputManager::SetRelativeMouseMode(true);
	
	//spawn player (it will make its camera active)
	Spawn(player);
	ResetCam();
	
	Ref<PBRMaterialInstance> material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	
	//	Ref<Texture> t = new Texture("youcantrun.png");
	//	material->SetAlbedoTexture(t);
	
	Ref<MeshAsset> sharedMesh = make_shared<MeshAsset>("cube.obj");
	
	anonymous = make_shared<RavEngine::Entity>();
	anonymous->EmplaceComponent<StaticMesh>(sharedMesh)->SetMaterial(material);
	Spawn(anonymous);
	anonymous->transform()->LocalTranslateDelta(vector3(0, 1, 0));
	
	InitPhysics();
	
	anonymousChild = make_shared<RavEngine::Entity>();
	anonymousChild->EmplaceComponent<StaticMesh>(sharedMesh)->SetMaterial(material);;
	anonymous->transform()->AddChild(anonymousChild->transform());
	anonymousChild->transform()->LocalTranslateDelta(vector3(17,0,0));
	anonymousChild->EmplaceComponent<PointLight>()->Intensity = 4;
	anonymousChild->EmplaceComponent<RigidBodyStaticComponent>();
	anonymousChild->EmplaceComponent<BoxCollider>(vector3(1,1,1),make_shared<PhysicsMaterial>(0.5,0.5,0.5));
	Spawn(anonymousChild);
	
	floorplane = make_shared<RavEngine::Entity>();
	floorplane->EmplaceComponent<StaticMesh>(sharedMesh)->SetMaterial(material);
	floorplane->transform()->LocalScaleDelta(vector3(10, 0.5, 10));
	floorplane->transform()->LocalTranslateDelta(vector3(0, -20, 0));
	floorplane->EmplaceComponent<RigidBodyStaticComponent>();
	floorplane->EmplaceComponent<BoxCollider>(vector3(10, 1, 10), make_shared<PhysicsMaterial>(0.5,0.5,0.5));
	Spawn(floorplane);
	
	dl = make_shared<Entity>();
	auto dll = dl->EmplaceComponent<DirectionalLight>();
	auto amt = glm::radians(45.0);
	dl->transform()->LocalRotateDelta(vector3(amt,0,0));
	dl->transform()->LocalTranslateDelta(vector3(0,1,1));
	dll->color = {1,0.5,0};
	Spawn(dl);
	
	ambientLight1 = make_shared<Entity>();
	auto light = ambientLight1->EmplaceComponent<AmbientLight>();
	light->Intensity = 1;
	light->color = {0.1, 0.2, 0.4};
	Spawn(ambientLight1);
}

TestWorld::TestWorld() : World() {
	
	
};
