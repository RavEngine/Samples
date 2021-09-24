#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/NavMeshComponent.hpp>

using namespace RavEngine;
using namespace std;

struct Level : public World{
    float deltaTime = 0;
    
    float cameraSpeed = 0.02;
    
    Ref<Entity> cameraRoot = Entity::New();
    Ref<Entity> cameraGimball = Entity::New();
    
    Ref<NavMeshComponent> navMesh;
    
    void CameraLR(float amt){
        cameraRoot->GetTransform()->LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball->GetTransform()->LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void Init(){
        auto cameraEntity = Entity::New();
        auto camera = cameraEntity->EmplaceComponent<CameraComponent>();
        camera->SetActive(true);
        cameraEntity->GetTransform()->LocalTranslateDelta(vector3(0,0,50));
        
        cameraRoot->GetTransform()->AddChild(cameraGimball->GetTransform());
        cameraGimball->GetTransform()->AddChild(cameraEntity->GetTransform());
        
        auto lightEntity = Entity::New();
        lightEntity->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
        lightEntity->EmplaceComponent<DirectionalLight>();
        lightEntity->GetTransform()->LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = Entity::New();
        auto gui = guiEntity->EmplaceComponent<GUIComponent>();
        auto doc = gui->AddDocument("ui.rml");
        
        auto im = App::inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->BindAxis("MouseX", gui, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gui, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gui);
        
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);
        
        im->BindAxis("CUD", static_pointer_cast<Level>(shared_from_this()), &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", static_pointer_cast<Level>(shared_from_this()), &Level::CameraLR, CID::ANY);
        
        // create the navigation object
        auto mazeEntity = Entity::New();
        MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
        auto mesh = MeshAsset::Manager::Get("maze.fbx", opt);
        mazeEntity->EmplaceComponent<StaticMesh>(mesh,RavEngine::New<PBRMaterialInstance>(Material::Manager::GetMaterial<PBRMaterial>()));
        navMesh = mazeEntity->EmplaceComponent<NavMeshComponent>(mesh,NavMeshComponent::Options());
        navMesh->CalculatePath(vector3(1,0,1), vector3(-1,0,-1));
        
        Spawn(cameraRoot);
        Spawn(cameraGimball);
        Spawn(cameraEntity);
        Spawn(mazeEntity);
        Spawn(lightEntity);
        Spawn(guiEntity);
    }
    
    void PostTick(float d) final{
        deltaTime = d;
    }
};

struct NavApp : public App{
    NavApp() : App(APPNAME) {}
    void OnStartup(int argc, char** argv) final {
        auto world = std::make_shared<Level>();
        world->Init();
        AddWorld(world);

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, Renderer->GetCurrentBackendName()).c_str());
    }
    
};

START_APP(NavApp)
