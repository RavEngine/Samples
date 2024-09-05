#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/AudioPlayer.hpp>
#include <RavEngine/VirtualFileSystem.hpp>
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>
#include <RavEngine/Window.hpp>
#include <numbers>

using namespace RavEngine;
using namespace std;

struct WhatMat : public RavEngine::UnlitMaterial {
	WhatMat() : UnlitMaterial("what", {
		.bindings = {
				 {
				.binding = 0,
				.type = RGL::BindingType::Sampler,
				.stageFlags = RGL::BindingVisibility::Fragment,
				},
				 {
					.binding = 1,
					.type = RGL::BindingType::SampledImage,
					.stageFlags = RGL::BindingVisibility::Fragment,
				},
			},
		}	
        ) {}
};
struct WhatMatInstance : public RavEngine::MaterialInstance{
    WhatMatInstance(Ref<WhatMat> m) : MaterialInstance(m) { };
    inline void SetTexture(Ref<Texture> texture) {
        textureBindings[1] = texture;
    }
};

struct RatsApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final;
	virtual void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
	}
};

static vector3 randomLaunchVector() {
	auto directionAngle = Random::get(0.f, 2 * std::numbers::pi_v<float>);

	return vector3(std::cos(directionAngle), 10, std::sin(directionAngle));
}

struct RatComponent : public ComponentWithOwner{
    double lastSoundTime = 0;
	double lastLaunchTime = 0;
	bool didTouchdown = false;
    RatComponent(entity_t owner) : ComponentWithOwner(owner){}
};

struct Rat : public RavEngine::GameObject {
	void Create(Ref<RavEngine::MaterialInstance> matInst, Ref<PhysicsMaterial> physMat) {
		GameObject::Create();

		GetTransform().LocalTranslateDelta(vector3(0,4,0));
		auto& body = EmplaceComponent<RigidBodyDynamicComponent>();

		
		body.SetLinearVelocity(randomLaunchVector(), true);
		body.EmplaceCollider<CapsuleCollider>(0.1f, 0.3f, physMat);
		body.debugEnabled = true;

		EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("rat.obj"), matInst);
        
        EmplaceComponent<RatComponent>();
	}
};

struct Pipe : public RavEngine::GameObject {
	void Create() {
		GameObject::Create();
		auto pipeMesh = MeshCollectionStaticManager::Get("pipe.obj");
		auto pipeMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		pipeMat->SetAlbedoTexture(Texture::Manager::Get("pipe.png"));
		EmplaceComponent<StaticMesh>(pipeMesh, pipeMat);

		auto& body = EmplaceComponent<RigidBodyStaticComponent>();
		auto physMat = RavEngine::New<PhysicsMaterial>();
		body.EmplaceCollider<CapsuleCollider>(1.0f, 1.0f, physMat, vector3{0,1.5,0}, vector3(0, 0, deg_to_rad(90.f)));

		body.debugEnabled = true;
	}
};

struct Floor : public RavEngine::GameObject {
	void Create() {
		GameObject::Create();

		constexpr static float floorSize = 20;
		GetTransform().SetLocalScale(vector3(floorSize, 1, floorSize));

		auto floorMesh = MeshCollectionStaticManager::Get("quad.obj");
		auto floorMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		floorMat->SetAlbedoColor({0.5,0.5,0.5,1});
		EmplaceComponent<StaticMesh>(floorMesh, floorMat);

		auto childObject = GetWorld()->Instantiate<GameObject>();
		GetTransform().AddChild(childObject);

		auto& body = childObject.EmplaceComponent<RigidBodyStaticComponent>();
		auto physMat = RavEngine::New<PhysicsMaterial>(0.5f, 0.5f, 0.5f);
		body.EmplaceCollider<BoxCollider>(vector3(floorSize, 0.5, floorSize), physMat);
		childObject.GetTransform().LocalTranslateDelta({0,-0.5,0});

		body.debugEnabled = true;
	}
};

struct What : public RavEngine::GameObject {
	void Create() {
		GameObject::Create();

		auto whatMesh = MeshCollectionStaticManager::Get("what.obj");
		auto whatMat = RavEngine::New<WhatMatInstance>(Material::Manager::Get<WhatMat>());
		whatMat->SetTexture(Texture::Manager::Get("what.png"));

		auto& mesh = EmplaceComponent<StaticMesh>(whatMesh, whatMat);
		mesh.SetEnabled(false);
	}
};

struct RatsWorld : public RavEngine::World {

	GameObject camRoot, camHeadUD, whatObj;
	constexpr static float camSpeed = 0.005;
	constexpr static float camTurnSpeed = 0.003;

	decimalType fsScale = 0;
	vector3 velvec{ 0,0,0 };
	bool relativeMouseMode = true;

	Ref<RavEngine::PBRMaterialInstance> ratmat;
	Ref<RavEngine::PhysicsMaterial> ratPhysMat;
    Ref<AudioAsset> whatMusic, swooshSound;
    
    std::vector<Ref<AudioAsset>> impactSounds;
    
    double lastWhatTime = -9;
	double lastRatTime = 0;
    
	constexpr static float minRatTime = 0.3;
	constexpr static float minRatSoundTime = 0.3;
	constexpr static float minRatLaunchTime = 5;

    constexpr static vector3 cameraResetPos = vector3(0,5,10);

	uint32_t soundsThisTick = 0;
	constexpr static uint32_t maxSounds = 20;

	
	RatsWorld() {
		InitPhysics();

		auto pipeEntity = Instantiate<Pipe>();
		Instantiate<Floor>();
	
		camRoot = Instantiate<decltype(camRoot)>();
		camHeadUD = Instantiate<decltype(camHeadUD)>();
		camRoot.GetTransform().AddChild(camHeadUD);
        
		whatObj = Instantiate<What>();
		camHeadUD.GetTransform().AddChild(whatObj);
		whatObj.GetTransform().LocalTranslateDelta(vector3(0,0,-0.5));
        
        camRoot.GetTransform().SetWorldPosition(cameraResetPos);

		auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
		cam.SetActive(true);
        camHeadUD.EmplaceComponent<AudioListener>();

		auto guiEntity = Instantiate<GameObject>();
		auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
		gui.AddDocument("main.rml");


		auto lightsEntity = Instantiate<GameObject>();
		auto& light = lightsEntity.EmplaceComponent<DirectionalLight>();	
		light.SetIntensity(4);
		light.SetCastsShadows(true);
		lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
        
        // audio room and listener
        auto roomEntity = Instantiate<GameObject>();
        auto& room = roomEntity.EmplaceComponent<SimpleAudioSpace>();
		room.SetRadius(30);

		lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });

		ratmat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		ratmat->SetAlbedoTexture(Texture::Manager::Get("rat.png"));
		ratPhysMat = RavEngine::New<PhysicsMaterial>(0.1f, 0.1f, 0.2f);
        
        whatMusic = RavEngine::New<RavEngine::AudioAsset>("what.ogg", 2),
        swooshSound = RavEngine::New<RavEngine::AudioAsset>("whoosh.ogg"),
        
        GetApp()->GetResources().IterateDirectory("sounds", [&](const string& track) {
            auto path = Filesystem::Path(track);
            auto filename = path.filename();
            
            if (filename == "what.ogg" || filename == "what.wav" || filename == "whoosh.ogg") return;

            impactSounds.push_back(RavEngine::New<AudioAsset>(filename.string()));
        });

		SetupInputs();

	}

	void RatCallback(float scale) {
		if (scale < 1.0) {
			return;
		}
		auto now = GetApp()->GetCurrentTime();
		if (now - lastRatTime < minRatTime) {
			return;
		}

		auto rat = Instantiate<Rat>(ratmat, ratPhysMat);
        
        auto callbackptr = RavEngine::New<RavEngine::PhysicsCallback>();
        callbackptr->OnColliderEnter = [rat, this](RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) mutable {
            auto index = Random::get<size_t>(0,impactSounds.size()-1);
            auto sound = impactSounds[index];
            auto pos = rat.GetTransform().GetWorldPosition();

			auto& ratComp = rat.GetComponent<RatComponent>();
			ratComp.didTouchdown = true;
			auto now = GetApp()->GetCurrentTime();
			if (now - ratComp.lastSoundTime < minRatSoundTime) {
				return;
			}
			ratComp.lastSoundTime = now;
            
			soundsThisTick++;
			if (soundsThisTick > maxSounds) {
				return;
			}

            GetApp()->DispatchMainThread([sound, pos, this](){
                PlaySound({sound, pos});
            });
        };
        rat.GetComponent<RigidBodyDynamicComponent>().AddReceiver(callbackptr);

		PlaySound({ swooshSound ,{0,5,0},1 });
		lastRatTime = now;
	}

	void WhatCallbackPressed() {
	
		whatObj.GetComponent<StaticMesh>().SetEnabled(true);
        auto now = GetApp()->GetCurrentTime();
        if (now - lastWhatTime >= 9.0){
            PlayAmbientSound(whatMusic);
            lastWhatTime = now;
        }
	}

	void WhatCallbackReleased() {
		whatObj.GetComponent<StaticMesh>().SetEnabled(false);
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
			* CreateRat = "CreateRat",
			* WhatAnim = "What",
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
		GetApp()->GetMainWindow()->SetRelativeMouseMode(relativeMouseMode);
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
		im->AddAxisMap(InputNames::CreateRat, SDL_SCANCODE_R);
		im->AddActionMap(InputNames::WhatAnim, SDL_SCANCODE_H);
        im->AddActionMap(InputNames::ResetCamera, SDL_SCANCODE_RETURN);

		im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

		im->BindAxis(InputNames::MoveUp, GetInput(this), &RatsWorld::CamMoveY, CID::ANY);
		im->BindAxis(InputNames::MoveForward, GetInput(this), &RatsWorld::CamMoveFwd, CID::ANY);
		im->BindAxis(InputNames::MoveRight, GetInput(this), &RatsWorld::CamMoveStrafe, CID::ANY);
		im->BindAxis(InputNames::LookRight, GetInput(this), &RatsWorld::CamLookLR, CID::ANY);
		im->BindAxis(InputNames::LookUp, GetInput(this), &RatsWorld::CamLookUD, CID::ANY);
		im->BindAxis(InputNames::CreateRat, GetInput(this), &RatsWorld::RatCallback, CID::ANY);

		im->BindAction(InputNames::WhatAnim, GetInput(this), &RatsWorld::WhatCallbackPressed, ActionState::Pressed, CID::ANY);
		im->BindAction(InputNames::WhatAnim, GetInput(this), &RatsWorld::WhatCallbackReleased, ActionState::Released, CID::ANY);

		im->BindAction(InputNames::ToggleMouse, GetInput(this), &RatsWorld::ToggleMouse, ActionState::Pressed, CID::ANY);
        im->BindAction(InputNames::ResetCamera, GetInput(this), &RatsWorld::CameraResetCallback, ActionState::Pressed, CID::ANY);
		GetApp()->GetMainWindow()->SetRelativeMouseMode(relativeMouseMode);

		GetApp()->inputManager = im;
	}

	void PreTick(float tickrateScale) final {
		fsScale = tickrateScale;

		camRoot.GetTransform().LocalTranslateDelta(velvec);
		velvec *= 0.9;
		soundsThisTick = 0;

		uint32_t counter = 0;
		auto allRats = GetAllComponentsOfType<RatComponent>();
		if (!allRats) {
			return;
		}
		
		auto launchRat = Random::get<int>(0ull, allRats->DenseSize()-5);
		if (launchRat < 0 || launchRat >= allRats->DenseSize()) {
			return;
		}

        Filter([this](const RatComponent& rat){
            auto owner = rat.GetOwner();
            if(owner.GetTransform().GetWorldPosition().y < -3){
                owner.Destroy();
            }
        });
       
		auto toLaunch = allRats->GetDense()[launchRat].GetOwner();
		auto& ratcomp = toLaunch.GetComponent<RatComponent>();
		if (ratcomp.didTouchdown) {
			auto now = GetApp()->GetCurrentTime();
			if (now - ratcomp.lastLaunchTime > minRatLaunchTime) {
				toLaunch.GetComponent<RigidBodyDynamicComponent>().SetLinearVelocity(randomLaunchVector() * 0.5f, true);
				ratcomp.lastLaunchTime = now;
			}
		}
	}
};

void RatsApp::OnStartup(int argc, char** argv) {

	SetWindowTitle("Crazy? I was crazy once...");

	auto level = RavEngine::New<RatsWorld>();

	AddWorld(level);
}

START_APP(RatsApp)
