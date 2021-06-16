#include "Level.hpp"
#include "Entity_And_Component.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <chrono>

using namespace std;
using namespace RavEngine;

STATIC(PA_Entity::num_objects);

struct MetricsSystem : public AutoCTTI {
	inline void Tick(float fpsScale, AccessReadWrite<GUIComponent> gc) {
		auto gui = gc.get();
		auto doc = gui->GetDocument("ui.rml");
		auto elem = doc->GetElementById("diag");
		gui->ExclusiveAccess([&] {
			elem->SetInnerRML(StrFormat(R"(<p>
FPS: {}({} ms) <br />
TPS : {} ({} ops/s) <br />
Entities : {} <br />
</p> 
)",
			(int)App::Renderer->GetCurrentFPS(), (int)App::Renderer->GetLastFrameTime(),
			FormatWithSep<int>(App::CurrentTPS()), FormatWithSep((int)App::CurrentTPS() * PA_Entity::num_objects * 2),
			FormatWithSep(PA_Entity::num_objects.load())
			));
		});

	}

	constexpr QueryIteratorAND<GUIComponent> QueryTypes() const{
		return QueryIteratorAND<GUIComponent>();
	}
};


void PerfA_World::OnActivate() {

	// register system
	systemManager.EmplaceSystem<CalcSystem>();
	systemManager.EmplaceTimedSystem<MetricsSystem>(std::chrono::seconds(1));

	// spawn demo entities
	for (int i = 0; i < 60000; i++) {
		Spawn(make_shared<PA_Entity>());
	}

	// spawn Control entity
	Ref<Entity> control = make_shared<Entity>();
	auto gui = control->EmplaceComponent<GUIComponent>();
	gui->AddDocument("ui.rml");

	Spawn(control);

	// input manager for the GUI
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);

	im->BindAxis("MouseX", gui, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gui, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(gui);

	App::inputManager = im;

}