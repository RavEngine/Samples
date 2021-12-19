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
#include <RavEngine/Utilities.hpp>
#include <array>

using namespace RavEngine;
using namespace std;

STATIC(PerfC_World::meshes);
STATIC(PerfC_World::textures);
STATIC(PerfC_World::TexturesEnabled) = true;
STATIC(PerfC_World::paused) = false;

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

struct DemoObject : public RavEngine::GameObject{
	void Create(Ref<DemoMaterialInstance> inst,bool isLight = false){
        GameObject::Create();
        
		auto child = GetWorld()->CreatePrototype<GameObject>();
		
		EmplaceComponent<ChildEntityComponent>(child);
        EmplaceComponent<SpinComponent>(vector3(spinrng(gen)/3,spinrng(gen)/3,spinrng(gen)/3));
		
        if (!isLight){
            inst->SetAlbedoColor({(float)colorrng(gen),(float)colorrng(gen),(float)colorrng(gen),1});
        }
        else{
            auto& light = child.EmplaceComponent<PointLight>();
            inst->SetAlbedoColor({1,1,1,1});
            light.Intensity = 5;
        }
		auto& mesh = child.EmplaceComponent<StaticMesh>(PerfC_World::meshes[meshrng(gen)],inst);
				
		GetTransform().AddChild(ComponentHandle<Transform>(child));
		
		child.GetTransform().LocalTranslateDelta(vector3(rng(gen),rng(gen),rng(gen)));
		
		child.EmplaceComponent<SpinComponent>(vector3(spinrng(gen),spinrng(gen),spinrng(gen)));
	}
};

void PerfC_World::OnActivate(){
	meshes[0] = MeshAsset::Manager::GetDefault("cube.obj");
	meshes[1] = MeshAsset::Manager::GetDefault("sphere.obj");
	meshes[2] = MeshAsset::Manager::GetDefault("cone.obj");
	meshes[3] = MeshAsset::Manager::GetDefault("cylinder.obj");
	
	auto cam = CreatePrototype<Camera>();
			
	lightEntity = CreatePrototype<GameObject>();
	auto& al = lightEntity.EmplaceComponent<AmbientLight>();
	al.Intensity = 0.3;
	
	auto& dl = lightEntity.EmplaceComponent<DirectionalLight>();
	dl.color = {0.7,1,1,1};
	dl.Intensity = 0.5;
	
	//load textures
	
    Array<Ref<DemoMaterialInstance>,PerfC_World::num_textures> materialInstances;
	
	Debug::Log("Loading {} textures", textures.size());
	for(int i = 0; i < textures.size(); i++){
		textures[i] = Texture::Manager::Get(StrFormat("tx{}.png",i+1));
		materialInstances[i] = make_shared<DemoMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		materialInstances[i]->SetAlbedoTexture(textures[i]);
    }
	
	Debug::Log("Loading {} objects", num_objects);
	//spawn the polygons
	for(int i = 0; i < num_objects; i++){
		Ref<DemoMaterialInstance> inst = materialInstances[texturerng(gen)];
        CreatePrototype<DemoObject>(inst);
	}
	
	//spawn the lights
	for(int i = 0; i < 3; i++){
		Ref<DemoMaterialInstance> inst = materialInstances[texturerng(gen)];
        CreatePrototype<DemoObject>(inst,true);
	}
			
	EmplaceSystem<SpinSystem,SpinComponent, RavEngine::Transform>();
    EmplaceSystem<PlayerSystem,Player>();
	
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

    ComponentHandle<Player> p(cam);
    	
	im->BindAxis("ZOOM", p, &Player::Zoom, CID::ANY);
	im->BindAxis("ROTATE_Y", p, &Player::RotateLR, CID::ANY);
	im->BindAxis("ROTATE_X", p, &Player::RotateUD, CID::ANY);
	
	GetApp()->inputManager = im;
	
	//create HUD
	auto hudentity = CreatePrototype<Entity>();
    hudentity.EmplaceComponent<GUIComponent>();
    hud = ComponentHandle<GUIComponent>(hudentity);
	auto doc = hud->AddDocument("main.rml");
	fpslabel = doc->GetElementById("fps");
	
	//button event listeners
	struct PauseEvtListener : public Rml::EventListener{
		
		PerfC_World* world;
		PauseEvtListener(decltype(world) s) : world(s){}
		
		void ProcessEvent(Rml::Event& evt) override{
			world->TogglePause();
		}
	};
	
	struct ToggleTxEvtListener : public Rml::EventListener{
		
        PerfC_World* world;
		ToggleTxEvtListener(decltype(world) w) : world(w){}
		
		void ProcessEvent(Rml::Event& evt) override{
			world->ToggleTextures();
		}
	};
	
	struct ToggleLightListener : public Rml::EventListener{
        PerfC_World* world;
		
		ToggleLightListener(decltype(world) w) : world(w){}
		
		void ProcessEvent(Rml::Event& evt) override{
            world->ToggleFullbright();
		}
	};
		
	doc->GetElementById("pause")->AddEventListener(Rml::EventId::Click, new PauseEvtListener(this));
	doc->GetElementById("toggletex")->AddEventListener(Rml::EventId::Click, new ToggleTxEvtListener(this));
	doc->GetElementById("toggleLighting")->AddEventListener(Rml::EventId::Click, new ToggleLightListener(this));
		
	// GUI bindings for mouse
	im->BindAnyAction(hud->GetData());
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	im->BindAxis("MouseX", hud, &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", hud, &GUIComponent::MouseY, CID::ANY,0);
	
	//gamepad bindings
	im->AddActionMap("PauseSim", ControllerButton::SDL_CONTROLLER_BUTTON_A);
	im->AddActionMap("ToggleTex", ControllerButton::SDL_CONTROLLER_BUTTON_B);
	im->AddActionMap("ToggleLight", ControllerButton::SDL_CONTROLLER_BUTTON_X);
    
    //TODO: FIX
	im->BindAction("PauseSim", GetInput(this), &PerfC_World::TogglePause, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleTex", GetInput(this), &PerfC_World::ToggleTextures, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleLight", GetInput(this), &PerfC_World::ToggleFullbright, ActionState::Pressed, CID::ANY);
}

void PerfC_World::PostTick(float scale){
	hud->EnqueueUIUpdate([this] {
		fpslabel->SetInnerRML(StrFormat("TPS: {}, FPS: {} ({} ms)", (int)GetApp()->CurrentTPS(),(int)GetApp()->GetRenderEngine().GetCurrentFPS(), (int)GetApp()->GetRenderEngine().GetLastFrameTime()));
	});
}

void PerfC_World::ToggleFullbright(){
	fullbright = !fullbright;
	auto fn = [this](float f, auto& al){
		al.Intensity = fullbright ? 1 : 0.5;
	};
    Filter<AmbientLight>(fn);
    Filter<DirectionalLight>(fn);
}
