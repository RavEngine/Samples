#include "Level.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/DebugDraw.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/InputManager.hpp>
#include "Character.hpp"
#include "CameraEntity.hpp"

using namespace RavEngine;
using namespace std;

void Level::SetupInputs(){
	
	Ref<Entity> lights = make_shared<Entity>();
	lights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	lights->transform()->LocalTranslateDelta(vector3(0,0.5,6));
	lights->EmplaceComponent<DirectionalLight>();
	lights->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	Spawn(lights);

	auto character = make_shared<Character>();
	character->transform()->LocalTranslateDelta(vector3(0,5,0));
	Spawn(character);

	auto im = App::inputManager = make_shared<InputManager>();
	im->AddAxisMap("MoveForward",SDL_SCANCODE_W);
	im->AddAxisMap("MoveForward", SDL_SCANCODE_S,-1);
	im->AddAxisMap("MoveRight", SDL_SCANCODE_A,-1);
	im->AddAxisMap("MoveRight", SDL_SCANCODE_D);

	im->AddActionMap("Test", SDL_SCANCODE_T);
	im->AddActionMap("Idle", SDL_SCANCODE_Y);
	im->BindAction("Test", character, &Character::SwitchAnimation, ActionState::Pressed, CID::ANY);
	im->BindAction("Idle", character, &Character::GoToIdle, ActionState::Pressed, CID::ANY);

	// load the game level
	auto floorplane = make_shared<RavEngine::Entity>();
	Ref<MeshAsset> sharedMesh = make_shared<MeshAsset>("cube.obj");
	Ref<PBRMaterialInstance> material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	floorplane->EmplaceComponent<StaticMesh>(sharedMesh)->SetMaterial(material);
	floorplane->transform()->LocalScaleDelta(vector3(10, 0.5, 10));
	floorplane->EmplaceComponent<RigidBodyStaticComponent>();
	floorplane->EmplaceComponent<BoxCollider>(vector3(10, 1, 10), make_shared<PhysicsMaterial>(0.5, 0.5, 0));
	Spawn(floorplane);

	auto camera = make_shared<CameraEntity>(character);
	camera->transform()->LocalTranslateDelta(vector3(0,2,5));
	Spawn(camera);

	InitPhysics();
}