#include <RavEngine/App.hpp>
#include "AppInfo.hpp"
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/NavMeshComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Dialogs.hpp>

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
    
    GameObject cameraRoot;
    GameObject cameraGimball;
    GameObject cameraEntity;
    Ref<MeshAsset> mesh;
    NavMeshComponent::Options nvopt;
    ComponentHandle<NavMeshComponent> navMesh;
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().CalculateWorldMatrix();
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void RecalculateNav(){
        GetComponent<NavMeshComponent>().UpdateNavMesh(mesh, nvopt);
    }
    
    Level(){
        InitPhysics();
        
        cameraRoot = CreatePrototype<GameObject>();
        cameraGimball = CreatePrototype<GameObject>();

        cameraEntity = CreatePrototype<GameObject>();
        auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
        camera.SetActive(true);
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,0,50));
        
        cameraRoot.GetTransform().AddChild(cameraGimball);
        cameraGimball.GetTransform().AddChild(cameraEntity);
        
        auto lightEntity = CreatePrototype<GameObject>();
        lightEntity.EmplaceComponent<AmbientLight>().Intensity = 0.2;
        lightEntity.EmplaceComponent<DirectionalLight>();
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = CreatePrototype<GameObject>();
        auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        ComponentHandle<GUIComponent> gh(guiEntity);
        
        auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gui.GetData());
        
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);
        
        auto owner = GetInput(this);
        
        im->BindAxis("CUD", owner, &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", owner, &Level::CameraLR, CID::ANY);
        
        // create the navigation object
        auto mazeEntity = CreatePrototype<GameObject>();
        MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
        mesh = MeshAsset::Manager::Get("maze.fbx", opt);
        mazeEntity.EmplaceComponent<StaticMesh>(mesh,RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
        auto& rigid = mazeEntity.EmplaceComponent<RigidBodyStaticComponent>();
        auto physmat = RavEngine::New<PhysicsMaterial>(0.5, 0.5, 0.5);
        rigid.EmplaceCollider<MeshCollider>(mesh,physmat);
        nvopt.agent.radius = 0.0001;
        nvopt.agent.maxClimb = 1;   // no climbing
        nvopt.cellSize = 0.2;
        nvopt.cellHeight = 0.2;
        mazeEntity.EmplaceComponent<NavMeshComponent>(mesh,nvopt);
        navMesh = ComponentHandle<NavMeshComponent>(mazeEntity);
        navMesh->debugEnabled = true;
        auto path = navMesh->CalculatePath(vector3(20,0,20), vector3(-20,0,-20));
        for(int i = 0; i < path.size(); i++){
            cout << path[i] << endl;
        }
        
        // connect the UI
        auto cellUpdater = new SliderUpdater([&,gh,doc](Rml::Event& evt) mutable{
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gh->EnqueueUIUpdate([=]{
                doc->GetElementById("cellSizeDisp")->SetInnerRML(field->GetValue());
            });
            GetApp()->DispatchMainThread([value,this]{
                
                nvopt.cellSize = value;
                nvopt.cellHeight = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("cellSize")->AddEventListener(Rml::EventId::Change, cellUpdater);
        
        auto radiusUpdater = new SliderUpdater([&,gh,doc](Rml::Event& evt) mutable{
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gh->EnqueueUIUpdate([=]{
                doc->GetElementById("agentRadiusDisp")->SetInnerRML(field->GetValue());
            });
            GetApp()->DispatchMainThread([value,this]{
                
                nvopt.agent.radius = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("agentRadius")->AddEventListener(Rml::EventId::Change, radiusUpdater);
        
        auto slopeUpdater = new SliderUpdater([&,gh,doc](Rml::Event& evt) mutable{
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gh->EnqueueUIUpdate([=]{
                doc->GetElementById("maxSlopeDisp")->SetInnerRML(field->GetValue());
            });
            GetApp()->DispatchMainThread([value,this]{
                
                nvopt.agent.maxSlope = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("maxSlope")->AddEventListener(Rml::EventId::Change, slopeUpdater);
        
        auto ball = CreatePrototype<GameObject>();
        ball.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("sphere.obj"),RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())).GetMaterial()->SetAlbedoColor({1,0,0,1});
        ball.EmplaceComponent<RigidBodyDynamicComponent>().EmplaceCollider<SphereCollider>(1,physmat);
        ball.GetTransform().LocalTranslateDelta(vector3(1,10,1));
        
    }
    
    void PostTick(float d) final{
        deltaTime = d;
    }
};

struct NavApp : public App{
    NavApp() : App(APPNAME) {}
    void OnStartup(int argc, char** argv) final {        
        auto world = RavEngine::New<Level>();
        AddWorld(world);

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};

START_APP(NavApp)
