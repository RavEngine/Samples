#include <RavEngine/App.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "AppInfo.hpp"
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;

struct Level : public RavEngine::World{
	GameObject cube;
	GameObject cameraRoot = Instantiate<decltype(cameraRoot)>(),cameraBoom = Instantiate<decltype(cameraBoom)>(), camera = Instantiate<decltype(camera)>();

	Level() {
		// load ground plane
		auto ground = Instantiate<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("quad.obj"), New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));
  
        cube = Instantiate<decltype(cube)>();
        auto cubeMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        cubeMat->SetAlbedoColor({0,0,1,1});
        cube.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("cube.obj"), cubeMat);
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

		auto light = Instantiate<GameObject>();
		auto& dl = light.EmplaceComponent<DirectionalLight>();
		dl.debugEnabled = false;
        dl.SetIntensity(3);
		dl.SetCastsShadows(true);
		light.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		light.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45))).LocalTranslateDelta(vector3(0,2,0));

	}
};

// level boilerplate
struct VRApp : public RavEngine::App {
	VRApp() {
		wantsXR = true;
	}
	void OnStartup(int argc, char** argv) final{
		AddWorld(RavEngine::New<Level>());
		SetWindowTitle(VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
	}
	void OnFatal(const std::string_view msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
	bool NeedsAudio() const final {
		return false;
	}
};
START_APP(VRApp);
