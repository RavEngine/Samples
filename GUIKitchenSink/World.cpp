#include "World.hpp"

#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>

using namespace RavEngine;
using namespace std;

void ::World::OnActivate(){
	//camera and cube
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->setActive(true);
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
	
	//input manager
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
	im->BindAxis("MouseX", doc, &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", doc, &GUIComponent::MouseY, CID::ANY,0);
	im->BindAnyAction(doc);
	
	App::inputManager = im;
}

void ::World::posttick(float scale){
	cube->transform()->LocalRotateDelta(vector3(glm::radians(1.0) * scale,glm::radians(-1.0 * scale),glm::radians(0.5) * scale));
}