#include <RavEngine/App.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "AppInfo.hpp"

using namespace RavEngine;
using namespace std;

struct Level : public RavEngine::World {
	GameObject tri, cube;
	GameObject cameraRoot = CreatePrototype<decltype(cameraRoot)>(), cameraBoom = CreatePrototype<decltype(cameraBoom)>(), camera = CreatePrototype<decltype(camera)>();

	struct InputNames {
		static constexpr char const
			* TurnLR = "TurnLR",
			* TurnUD = "TurnUD",
			* Zoom = "Zoom"
			;
	};

	float fpsScale = 1;
	static constexpr float turnSpeed = 1.2, moveSpeed = 0.2;

	void TurnLR(float amt) {
		cameraRoot.GetTransform().LocalRotateDelta(vector3(0, deg_to_rad(turnSpeed * amt * fpsScale), 0));
	}

	void TurnUD(float amt) {
		cameraBoom.GetTransform().LocalRotateDelta(vector3(deg_to_rad(turnSpeed * amt * fpsScale), 0, 0));
	}

	void Zoom(float amt) {
		camera.GetTransform().LocalTranslateDelta(vector3(0, 0, amt * fpsScale * moveSpeed));
	}

	Level() {
		// load ground plane
		auto ground = CreatePrototype<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"), LitMeshMaterialInstance(New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())));
		ground.GetTransform().LocalScaleDelta(vector3(5, 1, 5)).LocalRotateDelta(vector3(0, 0, deg_to_rad(-90))).SetWorldPosition(vector3(10, 0, 0));

		// load occludees
		vector3 positions[] = {
			{0,0,0},
			{0,5,0}
		};
		auto ballMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        ballMat->SetAlbedoColor(ColorRGBA{1,0,0,1});
		for (const auto& position : positions) {
			auto object = CreatePrototype<GameObject>();
			object.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("sphere.obj"), LitMeshMaterialInstance(ballMat));
			object.GetTransform().SetWorldPosition(position);
		}

		// create lights and camera
		auto& mainCam = camera.EmplaceComponent<CameraComponent>();
		mainCam.SetActive(true);
		camera.GetTransform().LocalTranslateDelta(vector3(0, 0, 20));
		cameraRoot.GetTransform().AddChild(cameraBoom);
		cameraBoom.GetTransform().AddChild(camera);

		auto light = CreatePrototype<GameObject>();
		auto& dl = light.EmplaceComponent<DirectionalLight>();
		dl.debugEnabled = false;
		dl.SetIntensity(0.8);
		dl.SetCastsShadows(true);
		light.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		light.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45))).LocalTranslateDelta(vector3(0, 2, 0));	

		auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
		im->AddAxisMap(InputNames::TurnLR, SDL_SCANCODE_D);
		im->AddAxisMap(InputNames::TurnLR, SDL_SCANCODE_A, -1);
		im->BindAxis(InputNames::TurnLR, GetInput(this), &Level::TurnLR, CID::ANY);
		im->AddAxisMap(InputNames::TurnUD, SDL_SCANCODE_W, -1);
		im->AddAxisMap(InputNames::TurnUD, SDL_SCANCODE_S);
		im->BindAxis(InputNames::TurnUD, GetInput(this), &Level::TurnUD, CID::ANY);
		im->AddAxisMap(InputNames::Zoom, SDL_SCANCODE_UP, -1);
		im->AddAxisMap(InputNames::Zoom, SDL_SCANCODE_DOWN);
		im->BindAxis(InputNames::Zoom, GetInput(this), &Level::Zoom, CID::ANY);

		// initial orientation
		TurnUD(-5);

	}
	void PostTick(float fpsScale) final {
		this->fpsScale = fpsScale;
	}
};

// level boilerplate
struct OcclusionApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final {
		AddWorld(RavEngine::New<Level>());
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
};
START_APP(OcclusionApp);
