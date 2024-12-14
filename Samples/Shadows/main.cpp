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
#include <RavEngine/GetApp.hpp>

using namespace RavEngine;
using namespace std;

struct Level : public RavEngine::World{
	GameObject tri, cube;
	GameObject cameraRoot = Instantiate<decltype(cameraRoot)>(),cameraBoom = Instantiate<decltype(cameraBoom)>(), camera = Instantiate<decltype(camera)>();

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
    
    struct PointLightMover{
        void operator()(const PointLight& p, Transform& t) const{
            auto time = GetApp()->GetCurrentTime();
            auto scale = GetApp()->GetCurrentFPSScale();
            t.SetLocalPosition({
                std::sin(time * 0.5) * 1.5 - 2,
                1,
                std::cos(time * 0.5) * 2 + 0.5,
            });
        }
    };

	Level() {
		// load ground plane
		auto ground = Instantiate<GameObject>();
		ground.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("quad"), New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
		ground.GetTransform().LocalScaleDelta(vector3(5,1,5));

		// load casting triangle
		tri = Instantiate<decltype(tri)>();
		constexpr static uint32_t trikey = 1;
		auto trimat = New<PBRMaterialInstance>(Material::Manager::GetWithKey<PBRMaterial>(trikey,MaterialRenderOptions{.cullMode = RGL::CullMode::None}));
		trimat->SetAlbedoColor({ 1,0,0,1 });
		tri.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("triangle"), trimat);
		tri.GetTransform().LocalTranslateDelta(vector3(-1.5, 0.8, 0))
            .LocalRotateDelta(vector3(deg_to_rad(90), deg_to_rad(90), deg_to_rad(180)))
            .LocalRotateDelta(vector3(0, deg_to_rad(90), 0));
  
        cube = Instantiate<decltype(cube)>();
        auto cubeMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        cubeMat->SetAlbedoColor({0,0,1,1});
        cube.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("cube"), cubeMat);
        cube.GetTransform()
            .LocalTranslateDelta(vector3(1,0.7,0))
            .LocalRotateDelta(vector3(deg_to_rad(45),deg_to_rad(90),0))
            //.LocalRotateDelta(vector3(0,0,deg_to_rad(45)))
            .SetLocalScale(0.5); 

		// create lights and camera
		auto& mainCam = camera.EmplaceComponent<CameraComponent>();
		mainCam.SetActive(true);
		mainCam.viewportOverride = {
			.sizeFactor = {0.5, 0.5}
		};
		camera.GetTransform().LocalTranslateDelta(vector3(0, 0, 5));
		cameraRoot.GetTransform().AddChild(cameraBoom);
		cameraBoom.GetTransform().AddChild(camera);

		// other cameras
		struct CamConfig {
			vector3 position;
			vector3 rotation;
			RavEngine::ViewportOverride viewport;
		};

		CamConfig cameras[]{ 
			{
				.position = {0,1,5},
				.rotation = {},
				.viewport = {
					.originFactor = {0.5,0},
					.sizeFactor = {0.5,0.5},
				}
			},
			{
				.position = {1,1,6},
				.rotation = {},
				.viewport = {
					.originFactor = {0,0.5},
					.sizeFactor = {0.5,0.5},
				}
			},
			{
				.position = {-1,1,7},
				.rotation = {},
				.viewport = {
					.originFactor = {0.5,0.5},
					.sizeFactor = {0.5,0.5},
				}
			}
		};

		for (const auto& cam : cameras) {
			auto camEntity = Instantiate<GameObject>();
			auto& camera = camEntity.EmplaceComponent<CameraComponent>();
			camera.SetEnabled(true);
			camera.SetActive(true);
			auto& camtransform = camEntity.GetTransform();

			camtransform.SetLocalPosition(cam.position);
			camtransform.SetLocalRotation(cam.rotation);
			camera.viewportOverride = cam.viewport;
		}


		auto light = Instantiate<GameObject>();
		auto& dl = light.EmplaceComponent<DirectionalLight>();
		dl.debugEnabled = false;
        dl.SetIntensity(0.8);
		dl.SetCastsShadows(true);
		light.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		light.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45))).LocalTranslateDelta(vector3(0,2,0));

        
        auto pointLight = Instantiate<GameObject>();
        auto& pLight = pointLight.EmplaceComponent<PointLight>();
        pLight.debugEnabled = true;
        pLight.SetColorRGBA({1,0,0,1});
        pLight.SetIntensity(2);
		pLight.SetCastsShadows(true);
         
        constexpr vector3 spotLightInitialPos{0,3,2};

		auto spotLightEntity = Instantiate<GameObject>();
		auto& spotLight = spotLightEntity.EmplaceComponent<SpotLight>();
		spotLight.SetCastsShadows(true);
		spotLight.debugEnabled = true;
		spotLightEntity.GetTransform().LocalTranslateDelta(spotLightInitialPos).LocalRotateDelta(vector3(deg_to_rad(30),0,0));
		spotLight.SetIntensity(10);
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
        
        EmplaceSystem<PointLightMover>();

        EmplaceSystem<decltype([=](const SpotLight&, Transform& t){
            auto time = GetApp()->GetCurrentTime();
            auto scale = GetApp()->GetCurrentFPSScale();
            t.SetLocalPosition({
                std::sin(time * 0.5) * 1.5 + spotLightInitialPos.x,
                spotLightInitialPos.y,
                spotLightInitialPos.z,
            });
        })>();

	}
	void PostTick(float fpsScale) final {
		this->fpsScale = fpsScale;
	}
};

// level boilerplate
struct VRApp : public RavEngine::App {
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
