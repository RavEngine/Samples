#include "Level.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/SceneLoader.hpp>
#include <FPSSystem.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsSolver.hpp>
#include <RavEngine/AnimatorSystem.hpp>
#include <RavEngine/PhysicsLinkSystem.hpp>
#include <RavEngine/MeshCollection.hpp>

#define NOCONTROLS 0

static Character character; // evil global for testing purposes

using namespace RavEngine;
using namespace std;

struct InputNames{
	static constexpr char const
		* MoveForward = "MoveForward",
		* MoveRight = "MoveRight",
		* Sprint = "Sprint",
		* Jump = "Jump",
		* Pound = "Pound",
		* ChangeChar = "ChangeChar";
};

constexpr static RavEngine::CacheBase::unique_key_t lvl_wall_key = 1;
constexpr static RavEngine::CacheBase::unique_key_t lvl_floors_key = 2;

Level::Level(){
	
	auto lights = Instantiate<GameObject>();
	lights.EmplaceComponent<AmbientLight>().SetIntensity(0.2f);
	auto& dl = lights.EmplaceComponent<DirectionalLight>();
	dl.SetCastsShadows(true);
	dl.SetIntensity(4);
    lights.GetTransform().LocalTranslateDelta(vector3(0,0.5,6)).LocalRotateDelta(vector3(deg_to_rad(45),deg_to_rad(45),0));
    auto& gui = lights.EmplaceComponent<GUIComponent>();
    gui.AddDocument("ui.rml");

	auto spawnCharacter = [this](Ref<MeshCollectionSkinned> mesh, Ref<PBRMaterialInstance> charMat, Ref<SkeletonAsset> skeleton, vector3 pos) {
		auto character2 = Instantiate<Character>(mesh, charMat, skeleton);
		character2.GetComponent<RigidBodyDynamicComponent>().setDynamicsWorldPose(pos, vector3(0, 0, 0));
		characters.push_back(character2);
	};

	{
		auto skeleton = RavEngine::New<SkeletonAsset>("character_bones");
		auto mesh = MeshCollectionSkinnedManager::Get("character_skin");
		auto charMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		charMat->SetAlbedoColor({ 1,0.4,0.2,1 });

		character = Instantiate<Character>(mesh, charMat, skeleton);
		character.GetComponent<RigidBodyDynamicComponent>().setDynamicsWorldPose(vector3(15, 5, 0), vector3(0, deg_to_rad(90), 0));
		characters.push_back(character);

		for (const vector3& vec : { vector3{ 5, 10, 0 }, vector3{-5, 10, 0} }) {
			spawnCharacter(mesh, charMat, skeleton, vec);
		}
	}
	
	// this one uses its own assets to be considered distinct by the engine
	{
		auto skeleton = RavEngine::New<SkeletonAsset>("character_bones");
		auto mesh = MeshCollectionSkinnedManager::Get("character_skin");
		auto charMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		charMat->SetAlbedoColor({ 0.2,0.4,1,1 });
		
		for (const vector3& vec : { vector3{ 5, 10, 10 }, vector3{-5, 10, 10} }) {
			spawnCharacter(mesh, charMat, skeleton, vec);
		}
	}

	
	
	camera = Instantiate<CameraEntity>(character);
	camera.GetTransform().LocalTranslateDelta(vector3(0,0,0));

	EmplaceSystem<CharacterScriptRunner>();
	EmplaceSystem<CameraScriptRunner>();
	CreateDependency<CharacterScriptRunner, CameraScriptRunner>();	// character script runs after camera script
	CreateDependency<AnimatorSystem, CharacterScriptRunner>();		// Animator system runs after the character script
	CreateDependency<PhysicsLinkSystemWrite, CharacterScriptRunner>();	// physics writer runs afer 
	
#if !NOCONTROLS
	auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
	// keyboard
	im->AddAxisMap(InputNames::MoveForward,SDL_SCANCODE_W);
	im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S,-1);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A,-1);
	im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
	im->AddAxisMap(InputNames::Sprint, SDL_SCANCODE_LSHIFT);
	im->AddActionMap(InputNames::Jump, SDL_SCANCODE_SPACE);
	im->AddActionMap(InputNames::Pound, SDL_SCANCODE_LCTRL);
	im->AddActionMap(InputNames::ChangeChar, SDL_SCANCODE_C);
	
	// AppleTV remote
	im->AddAxisMap(InputNames::Sprint, SDL_SCANCODE_PAUSE);
	im->AddActionMap(InputNames::Jump, SDL_SCANCODE_ESCAPE);

	// controller
	im->AddAxisMap(InputNames::MoveForward, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY, -1);
	im->AddAxisMap(InputNames::MoveRight, ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	im->AddAxisMap(InputNames::Sprint,  ControllerButton::SDL_CONTROLLER_BUTTON_X);
	im->AddActionMap(InputNames::Jump, ControllerButton::SDL_CONTROLLER_BUTTON_A);
	im->AddActionMap(InputNames::Pound, ControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	im->AddActionMap(InputNames::Pound, ControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	
	// controls are sent to the Camera, which then forwards them to the character after determining which way to move
	im->BindAxis(InputNames::MoveForward, camera, &CameraEntity::MoveForward, CID::ANY);
	im->BindAxis(InputNames::MoveRight, camera, &CameraEntity::MoveRight, CID::ANY);
	im->BindAxis(InputNames::Sprint, camera, &CameraEntity::SpeedIncrement, CID::ANY);
	im->BindAction(InputNames::Jump, camera, &CameraEntity::Jump, ActionState::Pressed, CID::ANY);
	im->BindAction(InputNames::Pound, camera, &CameraEntity::Pound, ActionState::Pressed, CID::ANY);
	im->BindAction(InputNames::ChangeChar, GetInput(this),&Level::ChangeChar, ActionState::Pressed, CID::ANY);
#else
#endif

	// load the game level
	Ref<PBRMaterialInstance> material = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	auto physmat = RavEngine::New<PhysicsMaterial>(0.5, 0.5, 0);
    MeshAssetOptions opt;
    opt.keepInSystemRAM = true;
	{
		auto floorplane = Instantiate<RavEngine::GameObject>();
		Ref<MeshAsset> sharedMesh = MeshAsset::Manager::GetWithKey("level_floors", lvl_floors_key, opt);
		material->SetAlbedoColor({ 174.f / 255,210.f / 255,234.f / 255,1 });
        floorplane.EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(sharedMesh), material);
		auto& r = floorplane.EmplaceComponent<RigidBodyStaticComponent>(FilterLayers::L0, FilterLayers::L0);
		r.EmplaceCollider<MeshCollider>(sharedMesh, physmat);
	}

	// load the walls
	auto walls = Instantiate<GameObject>();
	Ref<MeshAsset> sharedMesh = MeshAsset::Manager::GetWithKey("level_walls", lvl_wall_key, opt);
    walls.EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(sharedMesh),material);
	auto& s = walls.EmplaceComponent<RigidBodyStaticComponent>(FilterLayers::L1, FilterLayers::L1);	// we use L0 to determine floor vs walls
    s.EmplaceCollider<MeshCollider>(sharedMesh, physmat);

	InitPhysics();
    
    EmplaceTimedSystem<FPSSystem>(std::chrono::seconds(1), "ui.rml", "metrics");    
}

void Level::ChangeChar()
{
	currentChar++;
	currentChar %= characters.size();
	
	camera.GetComponent<CameraScript>().target = characters[currentChar];
}

void Level::PostTick(float)
{
#if NOCONTROLS
    character.Jump();  // spam jump
#endif
}
