#include "PerfC_World.hpp"
#include <RavEngine/Entity.hpp>
#include "Camera.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <fmt/format.h>
#include <RavEngine/Debug.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <array>

using namespace RavEngine;
using namespace std;

STATIC(PerfC_World::meshes);
STATIC(PerfC_World::textures);
STATIC(PerfC_World::TexturesEnabled) = true;
STATIC(PerfC_World::paused) = false;

static std::random_device rd; // obtain a random number from hardware
static std::mt19937 gen(rd()); // seed the generator
static std::uniform_int_distribution<> rng(-100, 100);
static std::uniform_int_distribution<> meshrng(0, PerfC_World::num_meshes - 1);
static std::uniform_int_distribution<> texturerng(0,PerfC_World::num_textures - 1);
static std::uniform_real_distribution<> spinrng(deg_to_rad(-1), deg_to_rad(1));
static std::uniform_real_distribution<> colorrng(0.5,1);

struct DemoObject : public RavEngine::GameObject{
	void Create(Ref<PBRMaterialInstance> inst,bool isLight = false){
        GameObject::Create();
        
		auto child = GetWorld()->CreatePrototype<GameObject>();
		
        EmplaceComponent<SpinComponent>(vector3(spinrng(gen)/3,spinrng(gen)/3,spinrng(gen)/3));
		
        if (!isLight){
            inst->SetAlbedoColor({(float)colorrng(gen),(float)colorrng(gen),(float)colorrng(gen),1});
        }
        else{
            auto& light = child.EmplaceComponent<PointLight>();
            inst->SetAlbedoColor({1,1,1,1});
            light.SetIntensity(5);
        }
		auto& mesh = child.EmplaceComponent<StaticMesh>(PerfC_World::meshes[meshrng(gen)],inst);
				
		GetTransform().AddChild(child);
		
		child.GetTransform().LocalTranslateDelta(vector3(rng(gen),rng(gen),rng(gen)));
		
		child.EmplaceComponent<SpinComponent>(vector3(spinrng(gen),spinrng(gen),spinrng(gen)));
	}
};

PerfC_World::PerfC_World(){
	meshes[0] = MeshAsset::Manager::Get("cube.obj");
	meshes[1] = MeshAsset::Manager::Get("sphere.obj");
	meshes[2] = MeshAsset::Manager::Get("cone.obj");
	meshes[3] = MeshAsset::Manager::Get("cylinder.obj");
	
	auto cam = CreatePrototype<Camera>();
			
	lightEntity = CreatePrototype<GameObject>();
	auto& al = lightEntity.EmplaceComponent<AmbientLight>();
	al.SetIntensity(0.3);
	
	auto& dl = lightEntity.EmplaceComponent<DirectionalLight>();
	dl.SetColorRGBA({0.7,1,1,1});
	dl.SetIntensity(0.5);
	dl.SetCastsShadows(true);
	
	//load textures
	
	Debug::Log("Loading {} textures", textures.size());
	for(int i = 0; i < textures.size(); i++){
		textures[i] = Texture::Manager::Get(StrFormat("tx{}.png",i+1));
		materialInstances[i] = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		materialInstances[i]->SetAlbedoTexture(textures[i]);
    }
	
	Debug::Log("Loading {} objects", num_objects);
	//spawn the polygons
	for(int i = 0; i < num_objects; i++){
		Ref<PBRMaterialInstance> inst = materialInstances[texturerng(gen)];
        CreatePrototype<DemoObject>(inst);
	}
	
	//spawn the lights
	for(int i = 0; i < 10; i++){
		Ref<PBRMaterialInstance> inst = materialInstances[texturerng(gen)];
        CreatePrototype<DemoObject>(inst,true);
	}
			
	EmplaceSystem<SpinSystem>();
    EmplaceSystem<PlayerSystem>();
	
	//bind inputs
	Ref<InputManager> im = RavEngine::New<InputManager>();
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
    
	im->BindAction("PauseSim", GetInput(this), &PerfC_World::TogglePause, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleTex", GetInput(this), &PerfC_World::ToggleTextures, ActionState::Pressed, CID::ANY);
	im->BindAction("ToggleLight", GetInput(this), &PerfC_World::ToggleFullbright, ActionState::Pressed, CID::ANY);
}

void PerfC_World::PostTick(float scale){
	hud->EnqueueUIUpdate([this] {
		fpslabel->SetInnerRML(StrFormat("TPS: {}, FPS: {} ({} ms)", (int)GetApp()->CurrentTPS(),(int)GetApp()->GetRenderEngine().GetCurrentFPS(), (int)GetApp()->GetRenderEngine().GetLastFrameTime()));
	});
}

void PerfC_World::ToggleTextures()
{
	TexturesEnabled = !TexturesEnabled;
	for (int i = 0; i < materialInstances.size(); i++) {
		if (TexturesEnabled) {
			materialInstances[i]->SetAlbedoTexture(textures[i]);
		}
		else {
			materialInstances[i]->SetAlbedoTexture(Texture::Manager::defaultTexture);
		}
	}
	
}

void PerfC_World::ToggleFullbright(){
	fullbright = !fullbright;
	const auto fn = [this](auto& al){
		al.SetIntensity(fullbright ? 1 : 0.5);
	};
	Filter([&](AmbientLight& al) {
		fn(al);
	});
    Filter([&](DirectionalLight& al) {
		fn(al);
	});
}
