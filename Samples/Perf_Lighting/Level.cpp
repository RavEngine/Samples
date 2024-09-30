#include "Level.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include "LightEntity.hpp"
#include <RavEngine/SystemInfo.hpp>
#include <FPSSystem.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;

struct SpinComponent : public AutoCTTI {
	float speed = Random::get(0.3,1.5);
};

struct SpinSystem : public RavEngine::AutoCTTI {

	inline void operator()(const SpinComponent& s, Transform& t) const {
        auto fpsScale = GetApp()->GetCurrentFPSScale();
		t.LocalRotateDelta(vector3(0,deg_to_rad(fpsScale * s.speed),0));
	}
};

struct ObjectMarker : public ComponentWithOwner {
    ObjectMarker(RavEngine::Entity owner) : ComponentWithOwner(owner){}
};

struct StaticMeshEntity : public GameObject {
	void Create(Ref<MeshCollectionStatic> mesh, Ref<PBRMaterialInstance> mat) {
        GameObject::Create();
		EmplaceComponent<StaticMesh>(mesh, mat).SetEnabled(false);
		EmplaceComponent<SpinComponent>();
		EmplaceComponent<ObjectMarker>();
		constexpr float dist = 1.0;
		GetTransform().LocalTranslateDelta(vector3(Random::get(-dist,dist), Random::get(-dist, dist), Random::get(-dist, dist)));
	}
};


Level::Level() {
	// load camera and lights
    auto camera = Instantiate<GameObject>();
	camera.EmplaceComponent<CameraComponent>().SetActive(true);
	camera.GetTransform().LocalTranslateDelta(vector3(0, 0.5, 2));

	// GUI
	auto& g = camera.EmplaceComponent<GUIComponent>();
	auto doc = g.AddDocument("ui.rml");
	
	struct SliderHandler : public Rml::EventListener {
		Level* world;
		decltype(doc) document;
		SliderHandler(decltype(world) l, decltype(document) d) : world(l), document(d) {}

		void ProcessEvent(Rml::Event& event) final {
			auto field = static_cast<Rml::ElementFormControlInput*>(document->GetElementById("numobjs"));
			auto value = std::stoi(field->GetValue());

			const auto objects = world->GetAllComponentsOfType<ObjectMarker>();
			for (const auto& obj : *objects) {
				obj.GetOwner().GetComponent<StaticMesh>().SetEnabled(false);
			}
			int i = 1;
			for (const auto& obj : *objects) {
				obj.GetOwner().GetComponent<StaticMesh>().SetEnabled(true);
				if (i >= value) {
					break;
				}
				i++;
			}
            world->GetComponent<GUIComponent>().EnqueueUIUpdate([=] {
                document->GetElementById("readout")->SetInnerRML(Format("Number of objects: {}", value));
            });
		}
	};
	doc->GetElementById("numobjs")->AddEventListener(Rml::EventId::Change, new SliderHandler(this, doc));

	// inputs
	auto im = GetApp()->inputManager = RavEngine::New<RavEngine::InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
    
    ComponentHandle<GUIComponent> gh(camera);
	im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY, 0);
	im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY, 0);
	im->BindAnyAction(gh->GetData());

	auto lights = Instantiate<GameObject>();
	lights.EmplaceComponent<AmbientLight>().SetIntensity(0.1);
	lights.GetTransform().LocalRotateDelta(vector3(0,deg_to_rad(-30),deg_to_rad(45)));
	

	// load the ground plane
	auto ground = Instantiate<GameObject>();
    MeshAssetOptions opt;
	auto mesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("quad",opt));
	auto mat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	mat->SetAlbedoColor({0.2,0.2,0.2,1.0});
	ground.EmplaceComponent<StaticMesh>(mesh, mat);
	ground.GetTransform().SetLocalScale(1.2);

	// load the stanford dragon
	auto hmesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("dragon_stanford", opt));
	auto hmat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	
	for (int i = 0; i < 150; i++) {
		auto e = Instantiate<StaticMeshEntity>(hmesh, hmat);
		if (i == 0) {
			e.GetComponent<StaticMesh>().SetEnabled(true);
		}
	}

	// load Systems
	EmplaceSystem<SpinSystem>();
	EmplaceSystem<CirculateSystem>();
	EmplaceTimedSystem<FPSSystem>(chrono::seconds(1),"ui.rml","metrics");

	// load lights
	auto sphereMesh = New<MeshCollectionStatic>(RavEngine::MeshAsset::Manager::Get("sphere", opt));
	for (int i = 0; i < 5; i++) {
        Instantiate<LightEntity>(sphereMesh);
	}

}
