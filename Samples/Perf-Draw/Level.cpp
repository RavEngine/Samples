#include "Level.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <chrono>
#include "BasicEntity.hpp"
#include "Camera.hpp"
#include "CustomMaterials.hpp"

using namespace std;
using namespace RavEngine;

static constexpr uint32_t num_entities =
#ifdef _DEBUG
5000;
#else
200000;
#endif

struct MetricsSystem : public AutoCTTI {
	inline void operator()(float fpsScale, GUIComponent& gui) const{
		auto doc = gui.GetDocument("main.rml");
		auto elem = doc->GetElementById("diag");
		gui.EnqueueUIUpdate([this,elem] {
			elem->SetInnerRML(StrFormat(
				"FPS: {} ({} ms) <br /> TPS: {} <br /> Num Entities: {}",
				(int)GetApp()->GetRenderEngine().GetCurrentFPS(), (int)GetApp()->GetRenderEngine().GetLastFrameTime(),
				(int)GetApp()->CurrentTPS(),
				num_entities
			));
		});
	}
};

PerfB_World::PerfB_World() {

	Debug::Log("Loading Assets");
	auto matinst = RavEngine::New<InstanceColorMatInstance>(Material::Manager::Get<InstanceColorMat>());
	currentMesh = RavEngine::New<MeshAsset>();
	cube = RavEngine::MeshAsset::Manager::GetDefault("cube.obj");
	cone = RavEngine::MeshAsset::Manager::GetDefault("cone.obj");
	sphere = RavEngine::MeshAsset::Manager::GetDefault("sphere.obj");
	cylinder = RavEngine::MeshAsset::Manager::GetDefault("cylinder.obj");
	currentMesh->Exchange(cube);
    currentMesh->destroyOnDestruction = false;
	
	//systemManager.EmplaceTimedSystem<MetricsSystem>(std::chrono::seconds(1));

	// spawn demo entities
    Debug::Log("Spawning {} instances on entity",num_entities);
    CreatePrototype<InstanceEntity>(currentMesh,matinst,num_entities);

    auto player = CreatePrototype<Camera>();

	// spawn Control entity
    auto control = CreatePrototype<GameObject>();
	auto& gui = control.EmplaceComponent<GUIComponent>();
	auto& dirlight = control.EmplaceComponent<DirectionalLight>();
	auto& ambientLight = control.EmplaceComponent<AmbientLight>();
	ambientLight.Intensity = 0.3;
	auto doc = gui.AddDocument("main.rml");
	
	struct SelectionEventListener : public Rml::EventListener{
		
		PerfB_World* world;
		SelectionEventListener(PerfB_World* s) : world(s){}
		
		void ProcessEvent(Rml::Event& evt) override{
			auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
            world->SwitchMesh(static_cast<meshes>(selbox->GetSelection()));
		}
	};
	
	doc->GetElementById("sel")->AddEventListener(Rml::EventId::Change, new SelectionEventListener(this));
    
	// input manager for the GUI
	Ref<InputManager> im = RavEngine::New<InputManager>();
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

    ComponentHandle<GUIComponent> g(control);
	im->BindAxis("MouseX", g, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", g, &GUIComponent::MouseY, CID::ANY, 0);
    im->BindAnyAction(g->GetData());

	//player controls
    ComponentHandle<Player> h(player);
	im->BindAxis("ZOOM", h, &Player::Zoom, CID::ANY);
	im->BindAxis("ROTATE_Y", h, &Player::RotateLR, CID::ANY);
	im->BindAxis("ROTATE_X", h, &Player::RotateUD, CID::ANY);

	GetApp()->inputManager = im;

    // load systems
    EmplaceSystem<PlayerSystem,Player>();
    EmplaceTimedSystem<MetricsSystem,GUIComponent>(std::chrono::seconds(1));
    
    ExportTaskGraph(cout);
}
