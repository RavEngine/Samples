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

using namespace RavEngine;
using namespace std;

std::array<Ref<MeshAsset>,PerfC_World::num_meshes> PerfC_World::meshes;
std::array<Ref<Texture>,PerfC_World::num_textures> PerfC_World::textures;
bool PerfC_World::TexturesEnabled = true;

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
		if (albedo.isNull()) {
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
		Ref<Entity> child = new Entity();
		
		AddComponent<ChildEntityComponent>(new ChildEntityComponent(child));
		AddComponent<SpinComponent>(new SpinComponent(vector3(spinrng(gen)/3,spinrng(gen)/3,spinrng(gen)/3)));
		
		auto mesh = child->AddComponent<StaticMesh>(new StaticMesh(PerfC_World::meshes[meshrng(gen)]));
		Ref<DemoMaterialInstance> inst = new DemoMaterialInstance(Material::Manager::AccessMaterialOfType<PBRMaterial>());
		
		if (!isLight){
			inst->SetAlbedoColor({(float)colorrng(gen),(float)colorrng(gen),(float)colorrng(gen),1});
			inst->SetAlbedoTexture(PerfC_World::textures[texturerng(gen)]);
		}
		else{
			auto light = child->AddComponent<PointLight>(new PointLight());
			inst->SetAlbedoColor({1,1,1,1});
			light->Intensity = 5;
		}
		mesh->SetMaterial(inst);
		
		transform()->AddChild(child->transform());
		
		child->transform()->LocalTranslateDelta(vector3(rng(gen),rng(gen),rng(gen)));
		
		child->AddComponent<SpinComponent>(new SpinComponent(vector3(spinrng(gen),spinrng(gen),spinrng(gen))));
	}
};

PerfC_World::PerfC_World(){
	meshes[0] = new MeshAsset("cube.obj");
	meshes[1] = new MeshAsset("sphere.obj");
	meshes[2] = new MeshAsset("cone.obj");
	meshes[3] = new MeshAsset("cylinder.obj");
	
	Ref<Camera> cam = new Camera();
	
	Spawn(cam);
	
	lightEntity = new Entity();
	auto al = lightEntity->AddComponent<AmbientLight>(new AmbientLight());
	al->Intensity = 0.3;
	
	auto dl = lightEntity->AddComponent<DirectionalLight>(new DirectionalLight());
	dl->color = {0.7,1,1,1};
	
	//load textures
	for(int i = 0; i < textures.size(); i++){
		textures[i] = new Texture(fmt::format("tx{}.png",i+1));
	}
	
	//spawn the polygons
	for(int i = 0; i < 3000; i++){
		Spawn(new DemoObject());
	}
	
	//spawn the lights
	for(int i = 0; i < 2; i++){
		Spawn(new DemoObject(true));
	}
	
	Spawn(lightEntity);
	
	spinsys = new SpinSystem();
	
	RegisterSystem<SpinSystem>(spinsys);
	
	//bind inputs
	Ref<InputManager> im = new InputManager();
	im->AddAxisMap("ZOOM", SDL_SCANCODE_UP);
	im->AddAxisMap("ZOOM", SDL_SCANCODE_DOWN, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_A, -1);
	im->AddAxisMap("ROTATE_Y", SDL_SCANCODE_D);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_W, -1);
	im->AddAxisMap("ROTATE_X", SDL_SCANCODE_S);
	
	im->AddAxisMap("ROTATE_Y", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);
	im->AddAxisMap("ROTATE_X", ControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
	im->AddAxisMap("ZOOM", ControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY);

	auto player = cam->GetComponent<Player>();
	
	im->BindAxis("ZOOM", player.get(), &Player::Zoom, CID::ANY);
	im->BindAxis("ROTATE_Y", player.get(), &Player::RotateLR, CID::ANY);
	im->BindAxis("ROTATE_X", player.get(), &Player::RotateUD, CID::ANY);
	
	App::inputManager = im;
	
	//create HUD
	Ref<Entity> hudentity = new Entity();
	auto hud = hudentity->AddComponent<GUIComponent>(new GUIComponent());
	auto doc = hud->AddDocument("main.rml");
	fpslabel = doc->GetElementById("fps");
	
	struct PauseEvtListener : public Rml::EventListener{
		
		WeakRef<SpinSystem> spinsys;
		PauseEvtListener(Ref<SpinSystem> s) : spinsys(s){}
		
		void ProcessEvent(Rml::Event& evt) override{
			spinsys.get()->paused = !spinsys.get()->paused;
		}
	};
	
	struct ToggleTxEvtListener : public Rml::EventListener{
		void ProcessEvent(Rml::Event& evt) override{
			PerfC_World::TexturesEnabled = !PerfC_World::TexturesEnabled;
		}
	};
	
	doc->GetElementById("pause")->AddEventListener("click", new PauseEvtListener(spinsys));
	doc->GetElementById("toggletex")->AddEventListener("click", new ToggleTxEvtListener());
	
	Spawn(hudentity);
	
	im->BindAnyAction<GUIComponent>(hud);
	
	im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
	im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
	
	im->BindAxis("MouseX", hud.get(), &GUIComponent::MouseX, CID::ANY,0);
	im->BindAxis("MouseY", hud.get(), &GUIComponent::MouseY, CID::ANY,0);
}

void PerfC_World::posttick(float scale){
	fpslabel->SetInnerRML(fmt::format("FPS: {}",round(App::evalNormal/scale)));
}
