#include "Level.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include "LightEntity.hpp"
#include <RavEngine/SystemInfo.hpp>

using namespace RavEngine;
using namespace std;

STATIC(LightEntity::lightmesh);

struct SpinComponent : public RavEngine::Component, public Queryable<SpinComponent> {
	float speed = Random::get(0.3,1.5);
};

struct SpinSystem : public RavEngine::AutoCTTI {

	inline void Tick(float fpsScale, Ref<SpinComponent> s, Ref<Transform> t) const {
		//s->Enabled = true;
		t->LocalRotateDelta(vector3(0,glm::radians(fpsScale * s->speed),0));
	}
};

struct ObjectMarker : public RavEngine::Component, public Queryable<ObjectMarker> {};

struct StaticMeshEntity : public Entity {
	StaticMeshEntity(Ref<MeshAsset> mesh, Ref<PBRMaterialInstance> mat) {
		EmplaceComponent<StaticMesh>(mesh, mat)->Enabled = false;
		EmplaceComponent<SpinComponent>();
		EmplaceComponent<ObjectMarker>();
		constexpr float dist = 1.0;
		GetTransform()->LocalTranslateDelta(vector3(Random::get(-dist,dist), Random::get(-dist, dist), Random::get(-dist, dist)));
	}
};

struct FPSSystem : public RavEngine::AutoCTTI {
	inline void Tick(float, Ref<GUIComponent> gui) {
		auto doc = gui->GetDocument("ui.rml");
		doc->GetElementById("metrics")->SetInnerRML(StrFormat("FPS: {} ({} ms)", std::round(App::Renderer->GetCurrentFPS()),std::round(App::Renderer->GetLastFrameTime())));
	};
};

void Level::OnActivate() {

	Debug::Log("{}", SystemInfo::GPUBrandString());

	// load camera and lights
	auto camera = make_shared<Entity>();
	camera->EmplaceComponent<CameraComponent>()->SetActive(true);
	camera->GetTransform()->LocalTranslateDelta(vector3(0, 0.5, 2));

	// GUI
	auto g = camera->EmplaceComponent<GUIComponent>();
	auto doc = g->AddDocument("ui.rml");
	
	struct SliderHandler : public Rml::EventListener {
		WeakRef<Level> level;
		decltype(doc) document;
		SliderHandler(decltype(level) l, decltype(document) d) : level(l), document(d) {}

		void ProcessEvent(Rml::Event& event) final {
			auto field = static_cast<Rml::ElementFormControlInput*>(document->GetElementById("numobjs"));
			auto value = std::stoi(field->GetValue());

			auto world = level.lock();
			const auto objects = world->GetAllComponentsOfType<ObjectMarker>();
			for (const auto& obj : objects) {
				obj->GetOwner().lock()->GetComponent<StaticMesh>().value()->Enabled = false;
			}
			int i = 1;
			for (const auto& obj : objects) {
				obj->GetOwner().lock()->GetComponent<StaticMesh>().value()->Enabled = true;
				if (i >= value) {
					break;
				}
				i++;
			}
			App::DispatchMainThread([&,world,value] {
				world->GetComponent<GUIComponent>().value()->ExclusiveAccess([&] {
						document->GetElementById("readout")->SetInnerRML(StrFormat("Number of objects: {}", value));
					});
			});
		}
	};
	doc->GetElementById("numobjs")->AddEventListener("change", new SliderHandler(static_pointer_cast<Level>(shared_from_this()), doc));

	// inputs
	auto im = App::inputManager = std::make_shared<RavEngine::InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", g, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", g, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(g);

	auto lights = make_shared<Entity>();
	lights->EmplaceComponent<AmbientLight>()->Intensity = 0.1;
	lights->GetTransform()->LocalRotateDelta(vector3(0,glm::radians(-30.f),glm::radians(45.f)));
	
	Spawn(camera);
	Spawn(lights);

	// load the ground plane
	auto ground = make_shared<Entity>();
	auto mesh = make_shared<MeshAsset>("quad.obj",1.2);
	auto mat = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	mat->SetAlbedoColor({0.2,0.2,0.2,1.0});
	ground->EmplaceComponent<StaticMesh>(mesh,mat);
	Spawn(ground);

	// load the stanford dragon
	auto hmesh = make_shared<MeshAsset>("dragon_vrip.ply", 2);
	auto hmat = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	
	for (int i = 0; i < 150; i++) {
		auto e = make_shared<StaticMeshEntity>(hmesh, hmat);
		if (i == 0) {
			e->GetComponent<StaticMesh>().value()->Enabled = true;
		}
		Spawn(e);
	}

	// load Systems
	systemManager.EmplaceSystem<SpinSystem>();
	systemManager.EmplaceSystem<CirculateSystem>();
	systemManager.EmplaceTimedSystem<FPSSystem>(chrono::seconds(1));

	// load lights
	for (int i = 0; i < 5; i++) {
		Spawn(make_shared<LightEntity>());
	}

}