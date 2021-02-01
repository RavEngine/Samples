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
#include <RavEngine/AudioRoom.hpp>
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
    
    RenderEngine::DebugPrint(1, 0x4f, "TPS: {}", round(App::CurrentTPS()));
    RenderEngine::DebugPrint(2, 0x4f, "TPS Scale: {}", fpsScale);
    RenderEngine::DebugPrint(3, 0x4f, "FPS: {}", round(App::Renderer->GetCurrentFPS()));
    RenderEngine::DebugPrint(4, 0x4f, "Frame Time: {} ms", App::Renderer->GetLastFrameTime());
    RenderEngine::DebugPrint(5, 0x4f, "Physics Bodies: {}", TestEntityController::objectcount.load());
	
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
	auto spotlight = anonymous->EmplaceComponent<SpotLight>();
	spotlight->Intensity = 4;
	spotlight->radius = 10;
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
	auto audioAsset = std::make_shared<RavEngine::AudioAsset>("vgaudio2.wav");
	//auto audiosource = anonymousChild->EmplaceComponent<RavEngine::AudioSourceComponent>(audioAsset);
	PlaySound(InstantaneousAudioSource(audioAsset,vector3(0,0,0),2));
	Spawn(anonymousChild);
	
	floorplane = make_shared<RavEngine::Entity>();
	floorplane->EmplaceComponent<StaticMesh>(sharedMesh)->SetMaterial(material);
	floorplane->transform()->LocalScaleDelta(vector3(10, 0.5, 10));
	floorplane->transform()->LocalTranslateDelta(vector3(0, -20, 0));
	floorplane->EmplaceComponent<RigidBodyStaticComponent>();
	floorplane->EmplaceComponent<BoxCollider>(vector3(10, 1, 10), make_shared<PhysicsMaterial>(0.5,0.5,0.5));
	
	auto room = floorplane->EmplaceComponent<AudioRoom>();
	RoomMaterial testMat({1,2,3,4,5,6,7,8});
	room->SetRoomDimensions(vector3(5,30,5));
	room->WallMaterials()[0] = RoomMat::kMarble;
//	room->WallMaterials()[1] = RoomMat::kMarble;
//	room->WallMaterials()[2] = RoomMat::kMarble;
//	room->WallMaterials()[3] = RoomMat::kMarble;
//	room->WallMaterials()[4] = RoomMat::kMarble;
//	room->WallMaterials()[5] = RoomMat::kMarble;

	//room->SetRoomMaterial(testMat);
	
//	audiosource->Play();
//	audiosource->SetLoop(true);
//	audiosource->SetVolume(5);
	
	struct RoomDebugRenderer : public IDebugRenderer{
		void DrawDebug(RavEngine::DebugDraw& dbg) const override{
			auto owner = std::static_pointer_cast<TestEntity>(getOwner().lock());
			if (owner){
				auto room = owner->GetComponent<AudioRoom>();
				if (room){
					room->DrawDebug(dbg);
				}
			}
		}
	};
	floorplane->EmplaceComponent<RoomDebugRenderer>();
	
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
