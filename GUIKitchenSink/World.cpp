#include "World.hpp"

#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/Debug.hpp>

using namespace RavEngine;
using namespace std;

struct SingleEntityMarker : public Component, public Queryable<SingleEntityMarker>{};

struct FPSSystem : public AutoCTTI {
	const RavEngine::System::list_type queries{ CTTI<SingleEntityMarker>() };
	void Tick(float scale, Ref<Component> c, ctti_t id){
		App::DispatchMainThread([](){
			App::SetWindowTitle(fmt::format("RavEngine GUIKitchenSink | {} - {} TPS, {} FPS ({} ms)", App::Renderer->currentBackend(), (int)App::CurrentTPS(), (int)App::Renderer->GetCurrentFPS(), (int)App::Renderer->GetLastFrameTime()).c_str());
		});
	}
	const RavEngine::System::list_type& QueryTypes() const{
		return queries;
	}
};
//System::list_type FPSSystem::queries;

void ::World::OnActivate(){
	//camera and cube
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->setActive(true);
	camlights->EmplaceComponent<SingleEntityMarker>();
	camlights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	camlights->transform()->LocalTranslateDelta(vector3(0,0,5));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	cube = make_shared<Entity>();
	auto cubemesh = cube->EmplaceComponent<StaticMesh>(make_shared<MeshAsset>("cube.obj"));
	cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	
	Ref<Entity> gui = make_shared<Entity>();
	auto doc = gui->EmplaceComponent<GUIComponent>();
	doc->AddDocument("sink.rml");
	
	Spawn(camlights);
	Spawn(cube);
	Spawn(dirlight);
	Spawn(gui);
	
	doc->Debug();
	
	//input manager
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
	im->BindAxis("MouseX", doc, &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", doc, &GUIComponent::MouseY, CID::ANY,0);
	im->BindAnyAction(doc);
	
	App::inputManager = im;
	
	//FPS updating system
	systemManager.RegisterTimedSystem(make_shared<FPSSystem>(), std::chrono::seconds(1));

	Debug::Log("{} with ID: {}",type_name<GUIComponent>(),CTTI<GUIComponent>());
}

void ::World::posttick(float scale){
	cube->transform()->LocalRotateDelta(vector3(glm::radians(1.0) * scale,glm::radians(-1.0 * scale),glm::radians(0.5) * scale));
}
