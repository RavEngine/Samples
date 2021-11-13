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
			FormatWithSep(PA_Entity::num_objects.load())
			));
		});

	}
};


void PerfA_World::OnActivate() {

	// register system
    
	EmplaceSystem<CalcSystem,SineComponent,CosComponent>();
	EmplaceTimedSystem<MetricsSystem,GUIComponent>(std::chrono::seconds(1));

	// spawn demo entities
	for (int i = 0; i < 60000; i++) {
        CreatePrototype<PA_Entity>();
	}

	// spawn Control entity
	auto control = CreatePrototype<Entity>();
	auto gui = control.EmplaceComponent<GUIComponent>();
    gui.AddDocument("ui.rml");


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
