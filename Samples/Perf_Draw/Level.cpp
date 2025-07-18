#include "Level.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <chrono>
#include "Camera.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "CustomMaterials.hpp"
#include <RavEngine/MeshCollection.hpp>
#include <RmlUi/Core.h>

using namespace std;
using namespace RavEngine;

static constexpr uint32_t num_entities =
#ifdef _DEBUG
5000;
#else
500000;
#endif

struct InstanceEntity : public RavEngine::GameObject {
	void Create(Ref<RavEngine::MeshCollectionStatic> mesh, Ref<InstanceColorMatInstance> matinst) {
		GameObject::Create();
		auto& ism = EmplaceComponent<RavEngine::StaticMesh>(mesh, matinst);
	}
};


struct MetricsSystem : public AutoCTTI {
	inline void operator()(GUIComponent& gui) const{
		auto doc = gui.GetDocument("main.rml");
		auto elem = doc->GetElementById("diag");
		gui.EnqueueUIUpdate([this,elem] {
			elem->SetInnerRML(Format(
				"TPS: {} <br /> Num Entities: {}",
				(int)GetApp()->CurrentTPS(),
				num_entities
			));
		});
	}
};

PerfB_World::PerfB_World() {

	Debug::Log("Loading Assets");
	matinst = RavEngine::New<InstanceColorMatInstance>(Material::Manager::Get<InstanceColorMat>());
	cube = RavEngine::MeshAsset::Manager::Get("cube");
	cone = RavEngine::MeshAsset::Manager::Get("cone");
	sphere = RavEngine::MeshAsset::Manager::Get("sphere");
	cylinder = RavEngine::MeshAsset::Manager::Get("cylinder");
	
	// spawn demo entities

	int32_t range = 200;

	meshCollection = New<MeshCollectionStatic>(cube);

    Debug::Log("Spawning {} instances",num_entities);
	for (uint32_t i = 0; i < num_entities; i++) {
		auto e = Instantiate<InstanceEntity>(meshCollection, matinst);
		auto& transform = e.GetTransform();

		vector3 pos;
		pos.x = RavEngine::Random::get(-range, range);
		pos.y = RavEngine::Random::get(-range, range);
		pos.z = RavEngine::Random::get(-range, range);

		vector3 rot(deg_to_rad(pos.x), deg_to_rad(pos.y), deg_to_rad(pos.z));

		transform.SetLocalPosition(pos);
		transform.SetLocalRotation(rot);
	}

    auto player = Instantiate<Camera>();

	// spawn Control entity
    auto control = Instantiate<GameObject>();
	auto& gui = control.EmplaceComponent<GUIComponent>();
	auto& dirlight = control.EmplaceComponent<DirectionalLight>();
	auto& ambientLight = control.EmplaceComponent<AmbientLight>();
	ambientLight.SetIntensity(0.6);
	dirlight.SetCastsShadows(false);
    dirlight.SetIntensity(4);
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
    EmplaceSystem<PlayerSystem>();
    EmplaceTimedSystem<MetricsSystem>(std::chrono::seconds(1));
}

void PerfB_World::SwitchMesh(meshes nextMesh)
{
	switch (nextMesh) {
	case meshes::cube:
		meshCollection->SetMeshForLOD(0, cube);
		break;
	case meshes::cone:
		meshCollection->SetMeshForLOD(0, cone);
		break;
	case meshes::cylinder:
		meshCollection->SetMeshForLOD(0, cylinder);
		break;
	case meshes::sphere:
		meshCollection->SetMeshForLOD(0, sphere);
		break;
	}
}

void PerfB_World::PreTick(float fpsscale)
{
	auto time = GetApp()->GetCurrentTime();
	matinst->SetTime(time);
}
