#include "PerfC_World.hpp"
#include <RavEngine/Entity.hpp>
#include "Camera.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <fmt/format.h>
#include <RavEngine/Debug.hpp>

using namespace RavEngine;
using namespace std;

std::array<Ref<MeshAsset>,PerfC_World::num_meshes> PerfC_World::meshes;
std::array<Ref<Texture>,PerfC_World::num_textures> PerfC_World::textures;
bool PerfC_World::TexturesEnabled = true;
const System::list_type SpinSystem::queries = {RavEngine::CTTI<SpinComponent>};

static std::random_device rd; // obtain a random number from hardware
static std::mt19937 gen(rd()); // seed the generator
static std::uniform_int_distribution<> rng(-40, 40);
static std::uniform_int_distribution<> meshrng(0, PerfC_World::num_meshes - 1);
static std::uniform_int_distribution<> texturerng(0,PerfC_World::num_textures - 1);
static std::uniform_real_distribution<> spinrng(glm::radians(-1.0), glm::radians(1.0));
static std::uniform_real_distribution<> colorrng(0.5,1);

struct DemoMaterialInstance : public RavEngine::PBRMaterialInstance{

	DemoMaterialInstance(Ref<PBRMaterial> m) : PBRMaterialInstance(m){}
	
	void DrawHook() override {
		if (!albedo) {
			albedo = TextureManager::defaultTexture;
		}

		if (PerfC_World::TexturesEnabled){
			albedo->Bind(0, mat->albedoTxUniform);
		}
		else{
			TextureManager::defaultTexture->Bind(0, mat->albedoTxUniform);
		}
		
		mat->albedoColorUniform.SetValues(&color, 1);
	}
};

struct DemoObject : public RavEngine::Entity{
	DemoObject(bool isLight = false){
		Ref<Entity> child = make_shared<Entity>();
		
		EmplaceComponent<ChildEntityComponent>(child);
        EmplaceComponent<SpinComponent>(vector3(spinrng(gen)/3,spinrng(gen)/3,spinrng(gen)/3));
		
		auto mesh = child->EmplaceComponent<StaticMesh>(PerfC_World::meshes[meshrng(gen)]);
		Ref<DemoMaterialInstance> inst = make_shared< DemoMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
		
		if (!isLight){
			inst->SetAlbedoColor({(float)colorrng(gen),(float)colorrng(gen),(float)colorrng(gen),1});
			inst->SetAlbedoTexture(PerfC_World::textures[texturerng(gen)]);
		}
		else{
			auto light = child->EmplaceComponent<PointLight>();
			inst->SetAlbedoColor({1,1,1,1});
			light->Intensity = 5;
		}
		mesh->SetMaterial(inst);
		
		transform()->AddChild(child->transform());
		
		child->transform()->LocalTranslateDelta(vector3(rng(gen),rng(gen),rng(gen)));
		
		child->EmplaceComponent<SpinComponent>(vector3(spinrng(gen),spinrng(gen),spinrng(gen)));
	}
};

PerfC_World::PerfC_World(){
	meshes[0] = make_shared<MeshAsset>("cube.obj");
	meshes[1] = make_shared<MeshAsset>("sphere.obj");
	meshes[2] = make_shared<MeshAsset>("cone.obj");
	meshes[3] = make_shared<MeshAsset>("cylinder.obj");
	
	Ref<Camera> cam = make_shared<Camera>();
	
	const auto shared_ptr_hack = std::shared_ptr<PerfC_World>(this, [](PerfC_World*){});
	
	Spawn(cam);
	
	lightEntity = make_shared<Entity>();
	auto al = lightEntity->EmplaceComponent<AmbientLight>();
	al->Intensity = 0.3;
	
	auto dl = lightEntity->EmplaceComponent<DirectionalLight>();
	dl->color = {0.7,1,1,1};
	dl->Intensity = 0.5;
	
	//load textures
	Debug::Log("Loading {} textures", textures.size());
	for(int i = 0; i < textures.size(); i++){
		textures[i] = make_shared<Texture>(fmt::format("tx{}.png",i+1));
	}
	
	Debug::Log("Loading {} objects", num_objects);
	//spawn the polygons
	for(int i = 0; i < num_objects; i++){
		Spawn(make_shared<DemoObject>());
	}
	
	//spawn the lights
	for(int i = 0; i < 3; i++){
		Spawn(make_shared<DemoObject>(true));
	}
	
	Spawn(lightEntity);
	
	spinsys = make_shared<SpinSystem>();
	
	systemManager.RegisterSystem<SpinSystem>(spinsys);
	
	//bind inputs
	Ref<InputManager> im = make_shared<InputManager>();
	im->AddAxisMap("ZOOM", SDL_SCANCODE_UP);
	im->AddAxisMap("ZOOM", SDL_SCANCODE_DOWN, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_A, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_D);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_W, -1);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_S);
	
	im->AddAxisMap("ROTATE_Y", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	im->AddAxisMap("ROTATE_X", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap("ZOOM", ControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY,-1);

	auto player = cam->GetComponent<Player>();
	
	im->BindAxis("ZOOM", player, &Player::Zoom, CID::ANY);
	im->BindAxis("ROTATE_Y", player, &Player::RotateLR, CID::ANY);
	im->BindAxis("ROTATE_X", player, &Player::RotateUD, CID::ANY);
	
	App::inputManager = im;
	
	//create HUD
	Ref<Entity> hudentity = make_shared<Entity>();
	hud = hudentity->EmplaceComponent<GUIComponent>();
	auto doc = hud->AddDocument("main.rml");
	fpslabel = doc->GetElementById("fps");
	
	//button event listeners
	struct PauseEvtListener : public Rml::EventListener{
		
		WeakRef<PerfC_World> world;
		PauseEvtListener(WeakRef<PerfC_World> s) : world(s){}
		
		void ProcessEvent(Rml::Event& evt) override{
			world.lock()->TogglePause();
		}
	};
	
	struct ToggleTxEvtListener : public Rml::EventListener{
		
		WeakRef<PerfC_World> world;
		ToggleTxEvtListener(WeakRef<PerfC_World> w) : world(w){}
		
		void ProcessEvent(Rml::Event& evt) override{
			world.lock()->ToggleTextures();
		}
	};
	
	struct ToggleLightListener : public Rml::EventListener{
		WeakRef<PerfC_World> world;
		
		ToggleLightListener(WeakRef<PerfC_World> w) : world(w){}
		
		void ProcessEvent(Rml::Event& evt) override{
			if(!world.expired()){
				world.lock()->ToggleFullbright();
			}
		}
	};
	
	auto ptr = shared_from_this();
	
	doc->GetElementById("pause")->AddEventListener("click", new PauseEvtListener(static_pointer_cast<PerfC_World>(ptr)));
	doc->GetElementById("toggletex")->AddEventListener("click", new ToggleTxEvtListener(static_pointer_cast<PerfC_World>(ptr)));
	doc->GetElementById("toggleLighting")->AddEventListener("click", new ToggleLightListener(static_pointer_cast<PerfC_World>(ptr)));
	
	Spawn(hudentity);
	
	// GUI bindings for mouse
	im->BindAnyAction(hud);
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", hud, &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", hud, &GUIComponent::MouseY, CID::ANY,0);
	
	//gamepad bindings
	im->AddActionMap("PauseSim", ControllerButton::SDL_CONTROLLER_BUTTON_A);
	im->AddActionMap("ToggleTex", ControllerButton::SDL_CONTROLLER_BUTTON_B);
	im->AddActionMap("ToggleLight", ControllerButton::SDL_CONTROLLER_BUTTON_X);
	im->BindAction("PauseSim", static_pointer_cast<PerfC_World>(ptr), &PerfC_World::TogglePause, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleTex", static_pointer_cast<PerfC_World>(ptr), &PerfC_World::ToggleTextures, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleLight", static_pointer_cast<PerfC_World>(ptr), &PerfC_World::ToggleFullbright, ActionState::Pressed, CID::ANY);
}

void PerfC_World::posttick(float scale){
	hud->ExclusiveAccess([&] {
		fpslabel->SetInnerRML(fmt::format("TPS: {}, FPS: {} ({} ms)", (int)App::CurrentTPS(),(int)RenderEngine::GetCurrentFPS(), (int)RenderEngine::GetLastFrameTime()));
	});
}

void PerfC_World::ToggleFullbright(){
	fullbright = !fullbright;
	
	auto dls = GetAllComponentsOfTypeFastPath<AmbientLight>();
	auto als = GetAllComponentsOfTypeFastPath<DirectionalLight>();
	
	for(auto dl : dls){
		static_pointer_cast<DirectionalLight>(dl)->Intensity = fullbright ? 1 : 0.5;
	}
	for(auto al : als){
        static_pointer_cast<AmbientLight>(al)->Intensity = fullbright ? 1 : 0.3;
	}
}
