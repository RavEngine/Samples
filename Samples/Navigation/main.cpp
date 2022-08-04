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
#include <RavEngine/DebugDrawer.hpp>

using namespace RavEngine;
using namespace std;

template<typename T>
struct RMLUpdater : public Rml::EventListener{
    T func;
    RMLUpdater(const T& f) : func(f){}
    void ProcessEvent(Rml::Event& evt) final{
        func(evt);
    }
};

static DebugDrawer dbgdraw;

struct Level : public World{
    float deltaTime = 0;
    
    float cameraSpeed = 0.02f;
    
    GameObject cameraRoot;
    GameObject cameraGimball;
    GameObject cameraEntity;
    Ref<MeshAsset> mesh;
    NavMeshComponent::Options nvopt;
    ComponentHandle<NavMeshComponent> navMesh;
    PhysicsBodyComponent::ColliderHandle<SphereCollider> ballCollider;
	
	RavEngine::Vector<vector3> path;
    vector3 startPos{ 20,0,20 }, endPos{ -20,0,-20 };
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().CalculateWorldMatrix();
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void RecalculateNav(){
        navMesh->UpdateNavMesh(mesh, nvopt);
		path = navMesh->CalculatePath(startPos, endPos);
    }

    std::optional<PhysicsSolver::RaycastHit> RaycastFromPixel(const vector2& pixel) {
        auto cam = cameraEntity.GetComponent<CameraComponent>();
        auto camRay = cam.ScreenPointToRay(pixel);
        auto camPos = cameraEntity.GetTransform().GetWorldPosition();
        PhysicsSolver::RaycastHit out_hit;
        bool hit = Solver.Raycast(camPos, camRay.second, 1000, out_hit);
        std::optional<PhysicsSolver::RaycastHit> hitobj;
        if (hit) {
            hitobj.emplace(std::move(out_hit));
        }
        return hitobj;
    }

    void SelectStart() {
        if (auto pos = RaycastFromPixel(InputManager::GetMousePosPixels())) {
            startPos = pos.value().hitPosition;
            RecalculateNav();
        }
    }

    void SelectEnd() {
        if (auto pos = RaycastFromPixel(InputManager::GetMousePosPixels())) {
            endPos = pos.value().hitPosition;
            RecalculateNav();
        }
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
        lightEntity.EmplaceComponent<AmbientLight>().Intensity = 0.2f;
        lightEntity.EmplaceComponent<DirectionalLight>().SetCastsShadows(true);
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = CreatePrototype<GameObject>();
        auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        ComponentHandle<GUIComponent> gh(guiEntity);
        
        auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S, -1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A, -1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);

        im->AddActionMap("ClickL", SDL_BUTTON_LEFT);
        im->AddActionMap("ClickR", SDL_BUTTON_RIGHT);

        im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gui.GetData());

        auto owner = GetInput(this);
        
        im->BindAxis("CUD", owner, &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", owner, &Level::CameraLR, CID::ANY);
        im->BindAction("ClickL", owner, &Level::SelectStart, ActionState::Pressed, CID::ANY);
        im->BindAction("ClickR", owner, &Level::SelectEnd, ActionState::Pressed, CID::ANY);
        
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
        navMesh->debugEnabled = false;
		RecalculateNav();
        
        // spawn the agent
        auto ball = CreatePrototype<GameObject>();
        ball.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("sphere.obj"),RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())).GetMaterial()->SetAlbedoColor({1,0,0,1});
        ballCollider = ball.EmplaceComponent<RigidBodyDynamicComponent>().EmplaceCollider<SphereCollider>(1,physmat);
        ball.GetComponent<RigidBodyDynamicComponent>().debugEnabled = true;
        ball.GetTransform().LocalTranslateDelta(vector3(1,10,1));
        
        // connect the UI
        auto cellUpdater = new RMLUpdater([&,gh,doc](Rml::Event& evt) mutable{
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
        
        auto radiusUpdater = new RMLUpdater([&,gh,doc](Rml::Event& evt) mutable{
            auto field = static_cast<Rml::ElementFormControlInput*>(evt.GetTargetElement());
            auto value = std::stof(field->GetValue());
            gh->EnqueueUIUpdate([=]{
                doc->GetElementById("agentRadiusDisp")->SetInnerRML(field->GetValue());
            });
            GetApp()->DispatchMainThread([value,this/*,ball,physmat*/]{
               // ball.GetComponent<RigidBodyDynamicComponent>().DestroyCollider(ballCollider);
                //ballCollider = ball.GetComponent<RigidBodyDynamicComponent>().EmplaceCollider<SphereCollider>(value,physmat);
                nvopt.agent.radius = value;
                RecalculateNav();
            });
           
        });
        doc->GetElementById("agentRadius")->AddEventListener(Rml::EventId::Change, radiusUpdater);
        
        auto slopeUpdater = new RMLUpdater([&,gh,doc](Rml::Event& evt) mutable{
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

        doc->GetElementById("showNav")->AddEventListener(Rml::EventId::Change, new RMLUpdater([this](Rml::Event& evt) mutable {
            navMesh->debugEnabled = evt.GetParameter("value", false);
        }));
        
    }
    
    void PostTick(float d) final{
        deltaTime = d;
		for (int i = 0; i < (int)path.size() - 1; i++){
			dbgdraw.DrawArrow(path[i], path[i+1], 0xFF0000FF);
		}
        {
            matrix4 transform(1);
            dbgdraw.DrawSphere(glm::translate(transform, startPos), 0xFF0000FF, 3);
        }
        {
            matrix4 transform(1);
            dbgdraw.DrawSphere(glm::translate(transform, endPos), 0x00FF00FF, 3);
        }
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
