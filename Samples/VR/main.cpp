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
	GameObject cube;
	GameObject cameraRoot = CreatePrototype<decltype(cameraRoot)>(),cameraBoom = CreatePrototype<decltype(cameraBoom)>(), camera = CreatePrototype<decltype(camera)>();

	Level() {
		// load ground plane
		auto ground = CreatePrototype<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"),New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));
  
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
        dl.Intensity = 0.8;
		dl.SetCastsShadows(true);
		light.EmplaceComponent<AmbientLight>().Intensity = 0.2;
		light.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45))).LocalTranslateDelta(vector3(0,2,0));

	}
};

// level boilerplate
struct ShadowApp : public RavEngine::App {
	ShadowApp() : App(APPNAME){
		wantsXR = true;
	}
	void OnStartup(int argc, char** argv) final{
		AddWorld(RavEngine::New<Level>());
		SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
};
START_APP(ShadowApp);
