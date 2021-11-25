#include "Level.hpp"
#include "Entity_And_Component.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/ComponentHandle.hpp>
#include <chrono>

using namespace std;
using namespace RavEngine;

STATIC(PA_Entity::num_objects);

struct MetricsSystem : public AutoCTTI {
	inline void operator()(float fpsScale, GUIComponent& gui) const{
		auto doc = gui.GetDocument("ui.rml");
		auto elem = doc->GetElementById("diag");
		gui.EnqueueUIUpdate([this,elem] {
			elem->SetInnerRML(StrFormat(R"(<p>
FPS: {}({} ms) <br />
TPS : {} ({} ops/s) <br />
Entities : {} <br />
</p> 
)",
			(int)App::GetRenderEngine().GetCurrentFPS(), (int)App::GetRenderEngine().GetLastFrameTime(),
			FormatWithSep<int>(App::CurrentTPS()), FormatWithSep((int)App::CurrentTPS() * PA_Entity::num_objects * 2),
			FormatWithSep(PA_Entity::num_objects)
			));
		});

	}
};

void PerfA_World::SetECSMode(int mode) {
	switch (lastMode) {
	case -1:
		break;	// nothing to do
	case 0:
		RemoveSystem<CalcSystem>();
		break;
	case 1:
		RemoveSystem<SingleSineSystem>();
		break;
	case 2:
		RemoveSystem<SingleSineSystem>();
		RemoveSystem<SingleCosSystem>();
		break;
	}

	switch (mode) {
	case 0:
		EmplaceSystem<CalcSystem, SineComponent, CosComponent>();
		break;
	case 1:
		EmplaceSystem<SingleSineSystem, SineComponent>();
		break;
	case 2:
		EmplaceSystem<SingleSineSystem, SineComponent>();
		EmplaceSystem<SingleCosSystem, CosComponent>();
		break;
	default:
		Debug::Fatal("Invalid ECS Mode : {}",mode);
	}
	lastMode = mode;
}


void PerfA_World::OnActivate() {

	// register system
	SetECSMode(1);
	EmplaceTimedSystem<MetricsSystem,GUIComponent>(std::chrono::seconds(1));

#ifdef _DEBUG
	static constexpr size_t num_objects = 600'000;	//reduced for demo because debug builds are slower
#else
	static constexpr size_t num_objects = 6'000'000;
#endif

	// spawn demo entities
	for (int i = 0; i < num_objects; i++) {
        CreatePrototype<PA_Entity>();
	}

	// spawn Control entity
	auto control = CreatePrototype<Entity>();
	auto gui = control.EmplaceComponent<GUIComponent>();
	auto doc = gui.AddDocument("ui.rml");

	// connect the dropdown
	struct SelectionEventListener : public Rml::EventListener {

		PerfA_World* world;
		SelectionEventListener(PerfA_World* s) : world(s) {}

		void ProcessEvent(Rml::Event& evt) override {
			auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
			auto idx = selbox->GetSelection();
			auto wptr = world;
			App::DispatchMainThread([wptr,idx] {
				wptr->SetECSMode(idx);
			});
		}
	};

	doc->GetElementById("sel")->AddEventListener(Rml::EventId::Change, new SelectionEventListener(this));

	// input manager for the GUI
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);

    ComponentHandle<GUIComponent> g(control);
	im->BindAxis("MouseX", g, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", g, &GUIComponent::MouseY, CID::ANY, 0);
    im->BindAnyAction(g->GetData());

	App::inputManager = im;

}
