#include <RavEngine/App.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/InputManager.hpp>
#include "AppInfo.hpp"

using namespace RavEngine;
using namespace std;

struct Level : public RavEngine::World{
	GameObject tri;
	GameObject cameraRoot = CreatePrototype<decltype(cameraRoot)>(),cameraBoom = CreatePrototype<decltype(cameraBoom)>(), camera = CreatePrototype<decltype(camera)>();

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
		cameraRoot.GetTransform().LocalRotateDelta(vector3(0, glm::radians(turnSpeed * amt * fpsScale), 0));
	}
	
	void TurnUD(float amt) {
		cameraBoom.GetTransform().LocalRotateDelta(vector3(glm::radians(turnSpeed * amt * fpsScale), 0, 0));
	}

	void Zoom(float amt) {
		camera.GetTransform().LocalTranslateDelta(vector3(0,0,amt * fpsScale * moveSpeed));
	}

	Level() {
		// load ground plane
		auto ground = CreatePrototype<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("quad.obj"),New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));

		// load casting triangle
		tri = CreatePrototype<decltype(tri)>();
		auto trimat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		trimat->doubleSided = true;
		trimat->SetAlbedoColor({ 1,0,0,1 });
		tri.EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("triangle.obj"),trimat);
		tri.GetTransform().LocalTranslateDelta(vector3(-1.5, 0.8, 0))
            .LocalRotateDelta(vector3(glm::radians(90.f), glm::radians(90.f), glm::radians(180.f)))
            .LocalRotateDelta(vector3(0, glm::radians(90.f), 0));

		// create lights and camera
		camera.EmplaceComponent<CameraComponent>().SetActive(true);
		camera.GetTransform().LocalTranslateDelta(vector3(0, 0, 5));
		cameraRoot.GetTransform().AddChild(cameraBoom);
		cameraBoom.GetTransform().AddChild(camera);

		auto light = CreatePrototype<GameObject>();
		light.EmplaceComponent<DirectionalLight>().debugEnabled = true;
        light.GetComponent<DirectionalLight>().Intensity = 0.5;
		light.EmplaceComponent<AmbientLight>().Intensity = 0.2;
		light.GetTransform().LocalRotateDelta(vector3(0, 0, glm::radians(30.f))).LocalTranslateDelta(vector3(0,2,0));
        
        auto pointLight = CreatePrototype<GameObject>();
        auto& pLight = pointLight.EmplaceComponent<PointLight>();
        pLight.debugEnabled = true;
        pLight.color = ColorRGBA{1,0,0,1};
        pLight.Intensity = 2;
        pointLight.GetTransform().LocalTranslateDelta(vector3(-2,1,-0.5));

		auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
		im->AddAxisMap(InputNames::TurnLR, SDL_SCANCODE_D);
		im->AddAxisMap(InputNames::TurnLR, SDL_SCANCODE_A, -1);
		im->BindAxis(InputNames::TurnLR, GetInput(this), &Level::TurnLR, CID::ANY);
		im->AddAxisMap(InputNames::TurnUD, SDL_SCANCODE_W,-1);
		im->AddAxisMap(InputNames::TurnUD, SDL_SCANCODE_S);
		im->BindAxis(InputNames::TurnUD, GetInput(this), &Level::TurnUD, CID::ANY);
		im->AddAxisMap(InputNames::Zoom, SDL_SCANCODE_UP,-1);
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
struct ShadowApp : public RavEngine::App {
	ShadowApp() : App(APPNAME) {}
	void OnStartup(int argc, char** argv) final{
		AddWorld(RavEngine::New<Level>());
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
};
START_APP(ShadowApp);
