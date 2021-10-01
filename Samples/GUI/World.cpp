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
	void Tick(float scale, Ref<SingleEntityMarker>){
		App::DispatchMainThread([](){
			App::SetWindowTitle(StrFormat("RavEngine GUIKitchenSink | {} - {} TPS, {} FPS ({} ms)", App::GetRenderEngine().GetCurrentBackendName(), (int)App::CurrentTPS(), (int)App::GetRenderEngine().GetCurrentFPS(), (int)App::GetRenderEngine().GetLastFrameTime()).c_str());
		});
	}
};
//System::list_type FPSSystem::queries;

void ::World::OnActivate(){
	//camera and cube
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->SetActive(true);
	camlights->EmplaceComponent<SingleEntityMarker>();
	camlights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	camlights->GetTransform()->LocalTranslateDelta(vector3(0,0,5));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->GetTransform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	cube = make_shared<Entity>();
	auto cubemesh = cube->EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("cube.obj"));
	cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
	
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

void ::World::PostTick(float scale){
	cube->GetTransform()->LocalRotateDelta(vector3(glm::radians(1.0) * scale,glm::radians(-1.0 * scale),glm::radians(0.5) * scale));
}
