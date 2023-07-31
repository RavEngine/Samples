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

struct Level : public RavEngine::World{
	GameObject tri, cube;
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
		cameraRoot.GetTransform().LocalRotateDelta(vector3(0, deg_to_rad(turnSpeed * amt * fpsScale), 0));
	}
	
	void TurnUD(float amt) {
		cameraBoom.GetTransform().LocalRotateDelta(vector3(deg_to_rad(turnSpeed * amt * fpsScale), 0, 0));
	}

	void Zoom(float amt) {
		camera.GetTransform().LocalTranslateDelta(vector3(0,0,amt * fpsScale * moveSpeed));
	}

	Level() {
		// load ground plane
		auto ground = CreatePrototype<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"),New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));

		// load casting triangle
		tri = CreatePrototype<decltype(tri)>();
		constexpr static uint32_t trikey = 1;
		auto trimat = New<PBRMaterialInstance>(Material::Manager::GetWithKey<PBRMaterial>(trikey,PBRMaterialOptions{.cullMode = RGL::CullMode::None}));
		trimat->SetAlbedoColor({ 1,0,0,1 });
		tri.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("triangle.obj"),trimat);
		tri.GetTransform().LocalTranslateDelta(vector3(-1.5, 0.8, 0))
            .LocalRotateDelta(vector3(deg_to_rad(90), deg_to_rad(90), deg_to_rad(180)))
            .LocalRotateDelta(vector3(0, deg_to_rad(90), 0));
  
        cube = CreatePrototype<decltype(cube)>();
        auto cubeMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        cubeMat->SetAlbedoColor({0,0,1,1});
        cube.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("cube.obj"),cubeMat);
        cube.GetTransform()
            .LocalTranslateDelta(vector3(1,0.7,0))
            .LocalRotateDelta(vector3(deg_to_rad(45),deg_to_rad(90),0))
            //.LocalRotateDelta(vector3(0,0,deg_to_rad(45)))
            .SetLocalScale(0.5); 

		// create lights and camera
		camera.EmplaceComponent<CameraComponent>().SetActive(true);
		camera.GetTransform().LocalTranslateDelta(vector3(0, 0, 5));
		cameraRoot.GetTransform().AddChild(cameraBoom);
		cameraBoom.GetTransform().AddChild(camera);

		auto light = CreatePrototype<GameObject>();
		auto& dl = light.EmplaceComponent<DirectionalLight>();
		dl.debugEnabled = false;
        dl.SetIntensity(0.8);
		dl.SetCastsShadows(true);
		light.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		light.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45))).LocalTranslateDelta(vector3(0,2,0));
        
        
        auto pointLight = CreatePrototype<GameObject>();
        auto& pLight = pointLight.EmplaceComponent<PointLight>();
        pLight.debugEnabled = true;
        pLight.SetColorRGBA({1,0,0,1});
        pLight.SetIntensity(2);
        pointLight.GetTransform().LocalTranslateDelta(vector3(-2,1,-0.5));
         

		auto spotLightEntity = CreatePrototype<GameObject>();
		auto& spotLight = spotLightEntity.EmplaceComponent<SpotLight>();
		spotLight.SetCastsShadows(true);
		spotLight.debugEnabled = true;
		spotLightEntity.GetTransform().LocalTranslateDelta(vector3(0,2,2)).LocalRotateDelta(vector3(deg_to_rad(30),0,0));
		spotLight.SetIntensity(2);
		auto sfwd = spotLightEntity.GetTransform().WorldForward();

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
	void OnStartup(int argc, char** argv) final{
		AddWorld(RavEngine::New<Level>());
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
};
START_APP(ShadowApp);
