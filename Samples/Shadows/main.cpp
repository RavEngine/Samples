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

	void Flip() {
		tri.GetTransform().LocalRotateDelta(vector3(0, glm::radians(90.f), 0));
	}

	Level() {
		// load ground plane
		auto ground = CreatePrototype<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("quad.obj"),New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));

		// load casting triangle
		tri = CreatePrototype<GameObject>();
		auto trimat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		trimat->doubleSided = true;
		trimat->SetAlbedoColor({ 1,0,0,1 });
		tri.EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("triangle.obj"),trimat);
		tri.GetTransform().LocalTranslateDelta(vector3(-1.5, 1, 0));
		tri.GetTransform().LocalRotateDelta(vector3(glm::radians(90.f), glm::radians(90.f), glm::radians(180.f)));
		tri.GetTransform().LocalRotateDelta(vector3(0, glm::radians(90.f), 0));

		// create lights and camera
		auto camera = CreatePrototype<GameObject>();
		camera.EmplaceComponent<CameraComponent>().SetActive(true);
		camera.GetTransform().LocalTranslateDelta(vector3(0, 1, 5));
		//camera.GetTransform().LocalRotateDelta(vector3(glm::radians(-20.f), 0, 0));

		auto light = CreatePrototype<GameObject>();
		light.EmplaceComponent<DirectionalLight>().debugEnabled = true;
		light.EmplaceComponent<AmbientLight>().Intensity = 0.2;
		light.GetTransform().LocalRotateDelta(vector3(0, 0, glm::radians(90.f)));

		auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
		im->AddActionMap("flip", SDL_SCANCODE_F);
		im->BindAction("flip", GetInput(this), &Level::Flip, Pressed, CID::ANY);

	}
	void PostTick(float fpsScale) final {
		//tri.GetTransform().LocalRotateDelta(vector3(0,glm::radians(0.3 * fpsScale),0));
		//tri.GetTransform().LocalRotateDelta(vector3(glm::radians(0.3 * fpsScale), 0, 0));
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