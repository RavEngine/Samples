//
//  WorldTest.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug.
//

#include "WorldTest.hpp"
#include "TestEntity.hpp"
#include "RavEngine/PhysicsLinkSystem.hpp"
#include "RavEngine/PhysicsBodyComponent.hpp"
#include "RavEngine/StaticMesh.hpp"
#include "RavEngine/PhysicsMaterial.hpp"
#include "RavEngine/ScriptSystem.hpp"
#include "RavEngine/BuiltinMaterials.hpp"
#include "RavEngine/InputManager.hpp"
#include "RavEngine/Light.hpp"
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/Window.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;
static GameObject anonymous;
static GameObject anonymousChild;
static GameObject floorplane;
static GameObject ambientLight1;
static GameObject dl;
static int ct = 0;

void TestWorld::SpawnEntities(float f) {
    if (f > 0.99) {
		Instantiate<TestEntity>();
    }
}

void TestWorld::ResetCam() {
	player.GetTransform().SetWorldPosition(vector3(0, -10, 50)).SetWorldRotation(quaternion());
}

void TestWorld::PostTick(float fpsScale){
    auto rotation = quaternion(vector3(0, 0, 0.01 * fpsScale));
    anonymous.GetTransform().LocalRotateDelta(rotation);
    scale = fpsScale;
	
	dl.GetTransform().LocalRotateDelta(vector3(0,0,deg_to_rad(1*fpsScale)));
}

TestWorld::TestWorld(){
    player = Instantiate<PlayerActor>();

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
	auto scHandle = ComponentHandle<PlayerScript>(player);
	is->BindAxis("MoveForward", scHandle, &PlayerScript::MoveForward,con);
	is->BindAxis("MoveRight", scHandle, &PlayerScript::MoveRight,con);
	is->BindAxis("MoveUp", scHandle,&PlayerScript::MoveUp,con);
	is->BindAxis("LookUp", scHandle,&PlayerScript::LookUp,con);
	is->BindAxis("LookRight", scHandle, &PlayerScript::LookRight,con);
		
	is->BindAxis("SpawnTest", GetInput(this), &TestWorld::SpawnEntities, con);
	is->BindAction("ResetCam", GetInput(this), &TestWorld::ResetCam, ActionState::Pressed,con);
	
	is->BindAxis("SpawnTest", GetInput(this), &TestWorld::SpawnEntities,con);
	is->BindAction("ResetCam", GetInput(this), &TestWorld::ResetCam, ActionState::Pressed,con);
	is->BindAction("SampleFPS", GetInput(this), &TestWorld::SampleFPS,ActionState::Pressed,con);
	//is->BindAction("Click", click, ActionState::Released);
	GetApp()->inputManager = is;
	
	GetApp()->GetMainWindow()->SetRelativeMouseMode(true);
	
	//spawn player (it will make its camera active)
	ResetCam();
	
	Ref<PBRMaterialInstance> material = make_shared<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	
	//	Ref<Texture> t = new Texture("youcantrun.png");
	//	material->SetAlbedoTexture(t);
	
	auto sharedMesh = MeshCollectionStaticManager::Get("cube");
	
	anonymous = Instantiate<GameObject>();
	anonymous.EmplaceComponent<StaticMesh>(sharedMesh, material);
	auto& spotlight = anonymous.EmplaceComponent<SpotLight>();
	spotlight.SetIntensity(4);
	spotlight.SetConeAngle(10);
	anonymous.GetTransform().LocalTranslateDelta(vector3(0, 1, 0));
	
	InitPhysics();
	
	anonymousChild = Instantiate<GameObject>();
	anonymousChild.EmplaceComponent<StaticMesh>(sharedMesh, material);
	anonymous.GetTransform().AddChild(anonymousChild);
	anonymousChild.GetTransform().LocalTranslateDelta(vector3(17,0,0));
	anonymousChild.EmplaceComponent<PointLight>().SetIntensity(4);
	auto& rs = anonymousChild.EmplaceComponent<RigidBodyStaticComponent>();
	rs.EmplaceCollider<BoxCollider>(vector3(1,1,1),make_shared<PhysicsMaterial>(0.5,0.5,0.5));
	//auto audioAsset = std::make_shared<RavEngine::AudioAsset>("creative2-3.ogg",2);
	//auto audiosource = anonymousChild->EmplaceComponent<RavEngine::AmbientAudioSourceComponent>(audioAsset);
	// PlaySound(InstantaneousAudioSource(audioAsset,vector3(0,0,0),2));
	//PlayAmbientSound(InstantaneousAmbientAudioSource(audioAsset));
	
	floorplane = Instantiate<GameObject>();
	floorplane.EmplaceComponent<StaticMesh>(sharedMesh, material);
	floorplane.GetTransform().LocalScaleDelta(vector3(10, 0.5, 10)).LocalTranslateDelta(vector3(0, -20, 0));
	auto& s = floorplane.EmplaceComponent<RigidBodyStaticComponent>();
	s.EmplaceCollider<BoxCollider>(vector3(10, 1, 10), make_shared<PhysicsMaterial>(0.5,0.5,0.5));
	
	auto& room = floorplane.EmplaceComponent<SimpleAudioSpace>();
	room.SetRadius(30);
	//room.WallMaterials()[0] = RoomMat::kMarble;
//	room->WallMaterials()[1] = RoomMat::kMarble;
//	room->WallMaterials()[2] = RoomMat::kMarble;
//	room->WallMaterials()[3] = RoomMat::kMarble;
//	room->WallMaterials()[4] = RoomMat::kMarble;
//	room->WallMaterials()[5] = RoomMat::kMarble;

	//room->SetRoomMaterial(testMat);
	
	//audiosource->Play();
	//audiosource->SetLoop(true);
//	audiosource->SetVolume(5);
		
	dl = Instantiate<GameObject>();
	auto& dll = dl.EmplaceComponent<DirectionalLight>();
	dll.SetCastsShadows(true);
	auto amt = deg_to_rad(45);
	dl.GetTransform().LocalRotateDelta(vector3(amt,0,0)).LocalTranslateDelta(vector3(0,1,1));
	dll.SetColorRGBA({1,0.5,0});
	
	ambientLight1 = Instantiate<GameObject>();
	auto& light = ambientLight1.EmplaceComponent<AmbientLight>();
	light.SetIntensity(1);
	light.SetColorRGBA({0.1, 0.2, 0.4});
}
