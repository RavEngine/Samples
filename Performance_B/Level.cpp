#include "Level.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <chrono>
#include "BasicEntity.hpp"
#include "Camera.hpp"
#include <RavEngine/QueryIterator.hpp>

using namespace std;
using namespace RavEngine;

static constexpr uint16_t num_entities =
#ifdef _DEBUG
5000;
#else
50000;
#endif

struct MetricsSystem : public AutoCTTI {
	inline void Tick(float fpsScale, AccessReadWrite<GUIComponent> gc) {
		auto gui = gc.get();
		auto doc = gui->GetDocument("main.rml");
		auto elem = doc->GetElementById("diag");
		gui->ExclusiveAccess([&] {
			elem->SetInnerRML(StrFormat(
				"FPS: {} ({} ms) <br /> TPS: {} <br /> Num Entities: {}",
				(int)App::Renderer->GetCurrentFPS(), (int)App::Renderer->GetLastFrameTime(),
				(int)App::CurrentTPS(),
				num_entities
			));
		});
	}

	constexpr QueryIteratorAND<GUIComponent> QueryTypes() const {
		return QueryIteratorAND<GUIComponent>();
	}
};

void PerfB_World::OnActivate() {

	Debug::Log("Loading Assets");
	auto matinst = make_shared<PBRMaterialInstance>(make_shared<PBRMaterial>());
	currentMesh = make_shared<MeshAsset>();
	cube = make_shared<MeshAsset>("cube.obj");
	cone = make_shared<MeshAsset>("cone.obj");
	sphere = make_shared<MeshAsset>("sphere.obj");
	cylinder = make_shared<MeshAsset>("cylinder.obj");
	currentMesh->Exchange(cube);
	
	systemManager.EmplaceTimedSystem<MetricsSystem>(std::chrono::seconds(1));

	// spawn demo entities

	Debug::Log("Spawning {} entities",num_entities);
	for (int i = 0; i < num_entities; i++) {
		Spawn(make_shared<BasicEntity>(currentMesh,matinst));
	}

	auto player = make_shared<Camera>();
	Spawn(player);

	// spawn Control entity
	Ref<Entity> control = make_shared<Entity>();
	auto gui = control->EmplaceComponent<GUIComponent>();
	auto dirlight = control->EmplaceComponent<DirectionalLight>();
	auto ambientLight = control->EmplaceComponent<AmbientLight>();
	ambientLight->Intensity = 0.3;
	auto doc = gui->AddDocument("main.rml");
	
	struct SelectionEventListener : public Rml::EventListener{
		
		WeakRef<PerfB_World> world;
		SelectionEventListener(WeakRef<PerfB_World> s) : world(s){}
		
		void ProcessEvent(Rml::Event& evt) override{
			auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
			world.lock()->SwitchMesh(static_cast<meshes>(selbox->GetSelection()));
		}
	};
	
	doc->GetElementById("sel")->AddEventListener("change", new SelectionEventListener(static_pointer_cast<PerfB_World>(shared_from_this())));

	Spawn(control);

	// input manager for the GUI
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);

	im->AddAxisMap("ZOOM", SDL_SCANCODE_UP);
	im->AddAxisMap("ZOOM", SDL_SCANCODE_DOWN, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_A, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_D);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_W, -1);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_S);

	im->AddAxisMap("ROTATE_Y", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	im->AddAxisMap("ROTATE_X", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap("ZOOM", ControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY, -1);

	im->BindAxis("MouseX", gui, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gui, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(gui);

	//player controls
	auto cam = player->GetComponent<Player>().value();
	im->BindAxis("ZOOM", cam, &Player::Zoom, CID::ANY);
	im->BindAxis("ROTATE_Y", cam, &Player::RotateLR, CID::ANY);
	im->BindAxis("ROTATE_X", cam, &Player::RotateUD, CID::ANY);

	App::inputManager = im;

}
