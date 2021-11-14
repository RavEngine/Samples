#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/NavMeshComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>

using namespace RavEngine;
using namespace std;

template<typename T>
struct SliderUpdater : public Rml::EventListener{
    T func;
    SliderUpdater(const T& f) : func(f){}
    void ProcessEvent(Rml::Event& evt) final{
        func(evt);
    }
};

struct Level : public World{
    float deltaTime = 0;
    
    float cameraSpeed = 0.02;
    
    Entity cameraRoot;
    Entity cameraGimball;
    Ref<MeshAsset> mesh;
    NavMeshComponent::Options nvopt;
    Ref<NavMeshComponent> navMesh;
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void RecalculateNav(){
        GetComponent<NavMeshComponent>().UpdateNavMesh(mesh, nvopt);
    }
    
    void Init(){
        InitPhysics();

        auto cameraEntity = CreatePrototype<GameObject>();
        auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
        camera.SetActive(true);
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,0,50));
        
        cameraRoot.GetTransform().AddChild(ComponentHandle<Transform>(cameraGimball));
        cameraGimball.GetTransform().AddChild(ComponentHandle<Transform>(cameraEntity));
        
        auto lightEntity = CreatePrototype<GameObject>();
        lightEntity.EmplaceComponent<AmbientLight>().Intensity = 0.2;
        lightEntity.EmplaceComponent<DirectionalLight>();
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = CreatePrototype<GameObject>();
        auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        
        auto im = App::inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->BindAxis("MouseX", gui, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gui, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gui.GetData());
        
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);
        
        im->BindAxis("CUD", static_pointer_cast<Level>(shared_from_this()), &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", static_pointer_cast<Level>(shared_from_this()), &Level::CameraLR, CID::ANY);
        
        // create the navigation object
        auto mazeEntity = CreatePrototype<GameObject>();
        MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
        mesh = MeshAsset::Manager::Get("maze.fbx", opt);
        mazeEntity.EmplaceComponent<StaticMesh>(mesh,RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
        mazeEntity.EmplaceComponent<RigidBodyStaticComponent>();
        auto physmat = RavEngine::New<PhysicsMaterial>(0.5, 0.5, 0.5);
        mazeEntity->EmplaceComponent<MeshCollider>(mesh,physmat);
        nvopt.agent.radius = 0.0001;
        nvopt.agent.maxClimb = 1;   // no climbing
        nvopt.cellSize = 0.2;
        nvopt.cellHeight = 0.2;
        navMesh = mazeEntity->EmplaceComponent<NavMeshComponent>(mesh,nvopt);
        navMesh->debugEnabled = true;
        //navMesh->CalculatePath(vector3(1,0,1), vector3(-1,0,-1));
        
        // connect the UI
        auto cellUpdater = new SliderUpdater([&,gui,doc](Rml::Event& evt){
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gui->EnqueueUIUpdate([=]{
                doc->GetElementById("cellSizeDisp")->SetInnerRML(field->GetValue());
            });
            App::DispatchMainThread([value,this]{
                
                nvopt.cellSize = value;
                nvopt.cellHeight = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("cellSize")->AddEventListener(Rml::EventId::Change, cellUpdater);
        
        auto radiusUpdater = new SliderUpdater([&,gui,doc](Rml::Event& evt){
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gui->EnqueueUIUpdate([=]{
                doc->GetElementById("agentRadiusDisp")->SetInnerRML(field->GetValue());
            });
            App::DispatchMainThread([value,this]{
                
                nvopt.agent.radius = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("agentRadius")->AddEventListener(Rml::EventId::Change, radiusUpdater);
        
        auto slopeUpdater = new SliderUpdater([&,gui,doc](Rml::Event& evt){
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gui->EnqueueUIUpdate([=]{
                doc->GetElementById("maxSlopeDisp")->SetInnerRML(field->GetValue());
            });
            App::DispatchMainThread([value,this]{
                
                nvopt.agent.maxSlope = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("maxSlope")->AddEventListener(Rml::EventId::Change, slopeUpdater);
        
        auto ball = Entity::New();
        ball->EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("sphere.obj"),RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
        ball->EmplaceComponent<RigidBodyDynamicComponent>();
        ball->EmplaceComponent<BoxCollider>(vector3(1,1,1),physmat);
        ball->GetTransform()->LocalTranslateDelta(vector3(0,10,0));
        ball->GetComponent<StaticMesh>().value()->GetMaterial()->SetAlbedoColor({1,0,0,1});
        
        Spawn(cameraRoot);
        Spawn(cameraGimball);
        Spawn(cameraEntity);
        Spawn(mazeEntity);
        Spawn(lightEntity);
        Spawn(guiEntity);
        Spawn(ball);
        
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

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    
};

START_APP(NavApp)
