#include "World.hpp"
#include <RavEngine/RenderEngine.hpp>
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
	void operator()(const SingleEntityMarker& s) const{
		GetApp()->DispatchMainThread([](){
			GetApp()->SetWindowTitle(VFormat("RavEngine GUIKitchenSink | {} - {} TPS", GetApp()->GetRenderEngine().GetCurrentBackendName(), (int)GetApp()->CurrentTPS()).c_str());
		});
	}
};

::World::World(){
	//camera and cube
	auto camlights = Instantiate<GameObject>();
	camlights.EmplaceComponent<CameraComponent>().SetActive(true);
	camlights.EmplaceComponent<SingleEntityMarker>();
	camlights.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
	camlights.GetTransform().LocalTranslateDelta(vector3(0,0,5));
	
	auto dirlight = Instantiate<GameObject>();
	dirlight.EmplaceComponent<DirectionalLight>().SetIntensity(4);
	dirlight.GetTransform().LocalRotateDelta(vector3(deg_to_rad(45),deg_to_rad(45),0));
	
	cube = Instantiate<GameObject>();
	auto& cubemesh = cube.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("cube.obj"), LitMeshMaterialInstance(RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())));
	
	auto gui = Instantiate<Entity>();
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
	EmplaceTimedSystem<FPSSystem>(std::chrono::seconds(1));

	Debug::Log("{} with ID: {}",type_name<GUIComponent>(),CTTI<GUIComponent>());
}

void ::World::PostTick(float scale){
    cube.GetTransform().LocalRotateDelta(vector3(deg_to_rad(1) * scale,deg_to_rad(-1 * scale),deg_to_rad(0.5) * scale));
}
