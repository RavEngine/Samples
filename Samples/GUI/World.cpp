#include "World.hpp"

#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/Debug.hpp>

using namespace RavEngine;
using namespace std;

struct SingleEntityMarker : public Queryable<SingleEntityMarker>{};

struct FPSSystem : public AutoCTTI {
	void operator()(float scale, const SingleEntityMarker& s) const{
		GetApp()->DispatchMainThread([](){
			GetApp()->SetWindowTitle(StrFormat("RavEngine GUIKitchenSink | {} - {} TPS, {} FPS ({} ms)", GetApp()->GetRenderEngine().GetCurrentBackendName(), (int)GetApp()->CurrentTPS(), (int)GetApp()->GetRenderEngine().GetCurrentFPS(), (int)GetApp()->GetRenderEngine().GetLastFrameTime()).c_str());
		});
	}
};

::World::World(){
	//camera and cube
	auto camlights = CreatePrototype<GameObject>();
	camlights.EmplaceComponent<CameraComponent>().SetActive(true);
	camlights.EmplaceComponent<SingleEntityMarker>();
	camlights.EmplaceComponent<AmbientLight>().Intensity = 0.2;
	camlights.GetTransform().LocalTranslateDelta(vector3(0,0,5));
	
	auto dirlight = CreatePrototype<GameObject>();
	dirlight.EmplaceComponent<DirectionalLight>();
	dirlight.GetTransform().LocalRotateDelta(vector3(deg_to_rad(45),deg_to_rad(45),0));
	
	cube = CreatePrototype<GameObject>();
	auto& cubemesh = cube.EmplaceComponent<StaticMesh>(MeshAsset::Manager::GetDefault("cube.obj"),RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
	
	auto gui = CreatePrototype<Entity>();
	auto& doc = gui.EmplaceComponent<GUIComponent>();
	doc.AddDocument("sink.rml");
	
	doc.Debug();
	
	//input manager
	Ref<InputManager> im = RavEngine::New<InputManager>();
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
    ComponentHandle<GUIComponent> g(gui);
	im->BindAxis("MouseX", g, &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", g, &GUIComponent::MouseY, CID::ANY,0);
	im->BindAnyAction(g->GetData());
	
	GetApp()->inputManager = im;
	
	//FPS updating system
	EmplaceTimedSystem<FPSSystem,SingleEntityMarker>(std::chrono::seconds(1));

	Debug::Log("{} with ID: {}",type_name<GUIComponent>(),CTTI<GUIComponent>());
}

void ::World::PostTick(float scale){
    cube.GetTransform().LocalRotateDelta(vector3(deg_to_rad(1) * scale,deg_to_rad(-1 * scale),deg_to_rad(0.5) * scale));
}
