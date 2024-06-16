#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioSpace.hpp>
#include "AppInfo.hpp"
#include <numbers>
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;

struct TransformsApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final;
	void OnFatal(const std::string_view msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
	}
	bool NeedsAudio() const final {
		return false;
	}
};


struct Level : public RavEngine::World {

	GameObject camRoot, camHeadUD, chainRoot;
	constexpr static float camSpeed = 0.005;
	constexpr static float camTurnSpeed = 0.003;

	decimalType fsScale = 0;
	vector3 velvec{ 0,0,0 };
	bool relativeMouseMode = true;

    constexpr static vector3 cameraResetPos = vector3(0,5,10);

	
	Level() {

		constexpr static float floorSize = 20;
		auto floor = Instantiate<GameObject>();
		floor.GetTransform().SetLocalScale(vector3(floorSize, 1, floorSize));

		{
			auto floorMesh = MeshCollectionStaticManager::Get("quad.obj");
			auto floorMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
			floorMat->SetAlbedoColor({ 0.5,0.5,0.5,1 });
			floor.EmplaceComponent<StaticMesh>(floorMesh, LitMeshMaterialInstance(floorMat));
		}
	
		camRoot = Instantiate<decltype(camRoot)>();
		camHeadUD = Instantiate<decltype(camHeadUD)>();
		camRoot.GetTransform().AddChild(camHeadUD);
        
		auto camParentedObject = Instantiate<GameObject>();
		{
			auto cylinderMesh = MeshCollectionStaticManager::Get("cylinder.obj");
			auto cylinderMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
			cylinderMat->SetAlbedoColor({ 1, 0, 0, 1 });
			camParentedObject.EmplaceComponent<StaticMesh>(cylinderMesh, LitMeshMaterialInstance(cylinderMat));
		}

		camHeadUD.GetTransform().AddChild(camParentedObject);
		camParentedObject.GetTransform().LocalTranslateDelta(vector3(2,0,-5));
        
        camRoot.GetTransform().SetWorldPosition(cameraResetPos);

		auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
		cam.SetActive(true);

		auto lightsEntity = Instantiate<GameObject>();
		auto& light = lightsEntity.EmplaceComponent<DirectionalLight>();	
		light.SetIntensity(4);
		light.SetCastsShadows(true);
		lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
       

		lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });

		chainRoot = Instantiate<GameObject>();
		{
			auto cubeMesh = MeshCollectionStaticManager::Get("cube.obj");
			auto cubeMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
			cubeMat->SetAlbedoColor({ 0, 1, 0, 1 });
			chainRoot.EmplaceComponent<StaticMesh>(cubeMesh, LitMeshMaterialInstance(cubeMat));
			chainRoot.GetTransform().SetWorldPosition(vector3(0, 1, 0));

			auto prevParent = chainRoot;

			for (int i = 0; i < 3; i++) {
				auto chainObj = Instantiate<GameObject>();
				chainObj.EmplaceComponent<StaticMesh>(cubeMesh, LitMeshMaterialInstance(cubeMat));
				prevParent.GetTransform().AddChild(chainObj);
				chainObj.GetTransform().SetLocalPosition(vector3(0,2,0));
				prevParent = chainObj;
			}
		}

		SetupInputs();
	}

    
    void CameraResetCallback() {
        camRoot.GetTransform().SetWorldPosition(cameraResetPos).SetWorldRotation(vector3(0,0,0));
    }

	struct InputNames {
		static constexpr char const
			* MoveForward = "MoveForward",
			* MoveRight = "MoveRight",
			* MoveUp = "MoveUp",
			* LookRight = "LookRight",
			* LookUp = "LookUp",
			* ToggleMouse = "ToggleMouse",
            * ResetCamera = "ResetCam"
			;
	};

	void CamMoveY(float amt) {
		velvec.y += amt * camSpeed * fsScale;
	}

	void CamMoveFwd(float amt) {
		velvec += camRoot.GetTransform().Forward() * amt * camSpeed * fsScale;
	}

	void CamMoveStrafe(float amt) {
		velvec += camRoot.GetTransform().Right() * amt * camSpeed * fsScale;
	}

	void CamLookLR(float amt) {
		if (relativeMouseMode) {
			camRoot.GetTransform().LocalRotateDelta(vector3(0, amt * camTurnSpeed * fsScale, 0));
		}
	}

	void CamLookUD(float amt) {
		if (relativeMouseMode) {
			camHeadUD.GetTransform().LocalRotateDelta(vector3(amt * camTurnSpeed * fsScale, 0, 0));
		}
	}

	void ToggleMouse() {
		relativeMouseMode = !relativeMouseMode;
		GetApp()->inputManager->SetRelativeMouseMode(relativeMouseMode);
	}

	void SetupInputs() {
		auto im = New<InputManager>();
		im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_SPACE);
		im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT, -1);
		im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
		im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S, -1);
		im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A, -1);
		im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
		im->AddAxisMap(InputNames::LookRight, Special::MOUSEMOVE_XVEL, -1);
		im->AddAxisMap(InputNames::LookUp, Special::MOUSEMOVE_YVEL, -1);
        im->AddActionMap(InputNames::ResetCamera, SDL_SCANCODE_RETURN);

		im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

		im->BindAxis(InputNames::MoveUp, GetInput(this), &Level::CamMoveY, CID::ANY);
		im->BindAxis(InputNames::MoveForward, GetInput(this), &Level::CamMoveFwd, CID::ANY);
		im->BindAxis(InputNames::MoveRight, GetInput(this), &Level::CamMoveStrafe, CID::ANY);
		im->BindAxis(InputNames::LookRight, GetInput(this), &Level::CamLookLR, CID::ANY);
		im->BindAxis(InputNames::LookUp, GetInput(this), &Level::CamLookUD, CID::ANY);

		im->BindAction(InputNames::ToggleMouse, GetInput(this), &Level::ToggleMouse, ActionState::Pressed, CID::ANY);
        im->BindAction(InputNames::ResetCamera, GetInput(this), &Level::CameraResetCallback, ActionState::Pressed, CID::ANY);
		im->SetRelativeMouseMode(relativeMouseMode);

		GetApp()->inputManager = im;
	}

	void PreTick(float scale) final {
		fsScale = scale;
	}

	void PostTick(float tickrateScale) final {
		camRoot.GetTransform().LocalTranslateDelta(velvec);
		velvec *= 0.9;

		auto now = GetApp()->GetCurrentTime();
		chainRoot.GetTransform().SetWorldPosition(vector3(std::sin(now * 3) * 5, 1, 0));
	}
};

void TransformsApp::OnStartup(int argc, char** argv) {

	SetWindowTitle(APPNAME);

	auto level = RavEngine::New<Level>();

	AddWorld(level);
}

START_APP(TransformsApp)
