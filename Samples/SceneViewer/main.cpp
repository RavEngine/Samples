#include <RavEngine/App.hpp>
#include <RavEngine/World.hpp>
#include <nfd.hpp>
#include <RavEngine/Filesystem.hpp>
#include <RavEngine/SceneLoader.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "AppInfo.hpp"

using namespace RavEngine;
using namespace std;

struct SceneViewerLevel : public RavEngine::World {
	GameObject camRoot, camHeadUD;
	constexpr static float camSpeed = 0.005;
	constexpr static float camTurnSpeed = 0.003;

	SceneViewerLevel() {

		// create camera
		camRoot = CreatePrototype<decltype(camRoot)>();
		camHeadUD = CreatePrototype<decltype(camHeadUD)>();
		camRoot.GetTransform().AddChild(camHeadUD);

		auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
		cam.SetActive(true);

		// default lights
		auto defaultLights = CreatePrototype<GameObject>();
		defaultLights.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		defaultLights.EmplaceComponent<DirectionalLight>().SetCastsShadows(true);
		defaultLights.GetTransform().LocalRotateDelta(vector3(0, 0, deg_to_rad(45)));
	}

	void AddData(const Filesystem::Path& path) {
		UnorderedMap<string_view, GameObject> nodes;
		SceneLoader loader(path);
		loader.LoadLocators([&](const Locator& loc) {
			auto obj = CreatePrototype<GameObject>();
			nodes[loc.name] = obj;
			auto& tr = obj.GetTransform();
			tr.SetWorldPosition(loc.translate);
			tr.SetWorldRotation(loc.rotation);
			tr.SetLocalScale(loc.scale);
		});

		auto defaultMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());

		loader.LoadMeshes([&](const PreloadedAsset&) -> bool {return true; }, [&](Ref<MeshAsset> asset, Ref<PBRMaterialInstance> mat, const PreloadedAsset& data) {
			try {
				nodes.at(data.name).EmplaceComponent<StaticMesh>(asset, mat);
			}
			catch (exception& e) {
				// continue silently...
			}
		});
	}

	struct InputNames {
		static constexpr char const
			* MoveForward = "MoveForward",
			* MoveRight = "MoveRight",
			* MoveUp = "MoveUp",
			* LookRight = "LookRight",
			* LookUp = "LookUp",
			* ToggleMouse = "ToggleMouse"
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
		im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT,-1);
		im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
		im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S,-1);
		im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A,-1);
		im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
		im->AddAxisMap(InputNames::LookRight, Special::MOUSEMOVE_XVEL,-1);
		im->AddAxisMap(InputNames::LookUp, Special::MOUSEMOVE_YVEL,-1);

		im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

		im->BindAxis(InputNames::MoveUp, GetInput(this), &SceneViewerLevel::CamMoveY, CID::ANY);
		im->BindAxis(InputNames::MoveForward, GetInput(this), &SceneViewerLevel::CamMoveFwd, CID::ANY);
		im->BindAxis(InputNames::MoveRight, GetInput(this), &SceneViewerLevel::CamMoveStrafe, CID::ANY);
		im->BindAxis(InputNames::LookRight, GetInput(this), &SceneViewerLevel::CamLookLR, CID::ANY);
		im->BindAxis(InputNames::LookUp, GetInput(this), &SceneViewerLevel::CamLookUD, CID::ANY);

		im->BindAction(InputNames::ToggleMouse, GetInput(this), &SceneViewerLevel::ToggleMouse, ActionState::Pressed, CID::ANY);
		im->SetRelativeMouseMode(relativeMouseMode);

		GetApp()->inputManager = im;
	}

	decimalType fsScale = 0;
	vector3 velvec{ 0,0,0 };
	bool relativeMouseMode = true;
	void PreTick(float scale) final {
		fsScale = scale;
	}

	void PostTick(float scale) final {
		camRoot.GetTransform().LocalTranslateDelta(velvec);
		velvec *= 0.9;
	}
};


struct SceneViewerApp : public RavEngine::App {
	bool LoadNewScene() {
		
		NFD::UniquePathU8 path;
		if (NFD::OpenDialog(path, nullptr, 0) == NFD_OKAY) {
			SetWindowTitle(StrFormat("{} - RavEngine SceneViewer | {} ",Filesystem::Path(path.get()).filename().string(), GetRenderEngine().GetCurrentBackendName()).c_str());
			static_pointer_cast<SceneViewerLevel>(GetCurrentRenderWorld())->AddData(path.get());
			return true;
		}
		else {
			return false;
		}
	}

	void OnStartup(int, char**) final {
		NFD::Init();
		auto scene = New<SceneViewerLevel>();
		scene->SetupInputs();
		AddWorld(scene);
		if (!LoadNewScene()) {
			Quit();
		}
	}

	int OnShutdown() final {
		NFD::Quit();

		return 0;
	}

	void OnFatal(const char* msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
	}
};

START_APP(SceneViewerApp)
