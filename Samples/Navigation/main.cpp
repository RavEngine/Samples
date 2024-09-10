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
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/PhysicsSolver.hpp>
#include <RavEngine/Window.hpp>
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>

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
    PhysicsBodyComponent::ColliderHandle ballCollider;
    
    Ref<PBRMaterialInstance> dottedLineMat, targetBeginMat, targetEndMat;
    GameObject targetBegin, targetEnd;
    
	
	RavEngine::Vector<vector3> path;
    vector3 startPos{ 20,0,20 }, endPos{ -20,0,-20 };
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void RecalculateNav(){
        navMesh->UpdateNavMesh(mesh, nvopt);
		path = navMesh->CalculatePath(startPos, endPos);
        DisplayNavPathWithDottedLine();
    }

    std::optional<PhysicsSolver::RaycastHit> RaycastFromPixel(const vector2& pixel) {
        auto cam = cameraEntity.GetComponent<CameraComponent>();
        auto res = GetApp()->GetMainWindow()->GetSizeInPixels();
        auto camRay = cam.ScreenPointToRay(pixel,res.width,res.height);
        auto camPos = cameraEntity.GetTransform().GetWorldPosition();
        PhysicsSolver::RaycastHit out_hit;
        bool hit = Solver->Raycast(camPos, camRay.second, 1000, out_hit);
        std::optional<PhysicsSolver::RaycastHit> hitobj;
        if (hit) {
            hitobj.emplace(std::move(out_hit));
        }
        return hitobj;
    }

    void SelectStart() {
        auto& win = GetApp()->GetMainWindow();
        if (auto pos = RaycastFromPixel(InputManager::GetMousePosPixels(win->GetDPIScale()))) {
            startPos = pos.value().hitPosition;
            RecalculateNav();
        }
    }

    void SelectEnd() {
        auto& win = GetApp()->GetMainWindow();
        if (auto pos = RaycastFromPixel(InputManager::GetMousePosPixels(win->GetDPIScale()))) {
            endPos = pos.value().hitPosition;
            RecalculateNav();
        }
    }
    
    void DisplayNavPathWithDottedLine(){
        struct DottedLineMarker : RavEngine::ComponentWithOwner{
            DottedLineMarker(entity_t owner) : ComponentWithOwner(owner){}
        };
        // delete all the previous dots
        if (auto allDots = GetAllComponentsOfType<DottedLineMarker>()){
            std::vector<Entity> dots;
            for(const auto& dot : *allDots){
                dots.push_back(dot.GetOwner());
                //dot.GetOwner().Destroy();
            }
            for (auto entity : dots) {
                entity.Destroy();
            }
        }
        
        auto sphereMeshCol = New<MeshCollectionStatic>(MeshAsset::Manager::Get("sphere"));
        auto drawDottedLine = [this,sphereMeshCol](const vector3& start, const vector3& end, decimalType step){
            vector3 point = start;
            auto scalefac = (step / 2) / 1.7f;
            auto dir = glm::normalize(start - end);
            const auto linelen = glm::length2(end - start);
            while(linelen > glm::length2(point - start)){ // use length2 for squared length
                auto dot = Instantiate<GameObject>();
                auto dotpt = point;
                dotpt.y += scalefac * 1.3;
                dot.GetTransform().SetWorldPosition(dotpt).SetLocalScale({scalefac});
                dot.EmplaceComponent<StaticMesh>(sphereMeshCol, dottedLineMat);
                dot.EmplaceComponent<DottedLineMarker>();
                point -= dir * step;
            }
        };
        
        for(int i = 0; i < path.size()-1; i++){
            drawDottedLine(path[i], path[i+1], std::max(nvopt.agent.radius * 2,0.3f));
        }
        targetBegin.GetTransform().SetWorldPosition(startPos);
        targetEnd.GetTransform().SetWorldPosition(endPos);
        targetBegin.GetTransform().SetLocalScale({2});
        targetEnd.GetTransform().SetLocalScale(targetBegin.GetTransform().GetLocalScale());
    }
    
    Level(){
        InitPhysics();
        
        dottedLineMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        dottedLineMat->SetAlbedoColor({0,1,0,1});
        
        cameraRoot = Instantiate<GameObject>();
        cameraGimball = Instantiate<GameObject>();
        
        targetBegin = Instantiate<GameObject>();
        targetEnd = Instantiate<GameObject>();
        auto targetBeginMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        targetBeginMat->SetAlbedoColor({1,0,0,1});
        auto targetEndMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        targetEndMat->SetAlbedoColor({0,0,1,1});

        auto targetMeshCol = New<MeshCollectionStatic>(MeshAsset::Manager::Get("target"));

        targetBegin.EmplaceComponent<StaticMesh>(targetMeshCol, targetBeginMat);
        targetEnd.EmplaceComponent<StaticMesh>(targetMeshCol, targetEndMat);

        cameraEntity = Instantiate<GameObject>();
        auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
        camera.SetActive(true);
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,0,50));
        
        cameraRoot.GetTransform().AddChild(cameraGimball);
        cameraGimball.GetTransform().AddChild(cameraEntity).LocalRotateDelta(vector3(deg_to_rad(-45),0,0));
        
        auto lightEntity = Instantiate<GameObject>();
        lightEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2f);
        auto& dirLight = lightEntity.EmplaceComponent<DirectionalLight>();
        dirLight.SetCastsShadows(true);
        dirLight.SetIntensity(4);
        dirLight.SetShadowDistance(70);
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = Instantiate<GameObject>();
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
        auto mazeEntity = Instantiate<GameObject>();
        MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
        mesh = MeshAsset::Manager::Get("maze", opt);
        mazeEntity.EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(mesh), RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
        // used for raycasting clicks onto the maze
        auto& rigid = mazeEntity.EmplaceComponent<RigidBodyStaticComponent>();
        rigid.debugEnabled = true;
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
            GetApp()->DispatchMainThread([value,this]() mutable{
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

#ifdef NDEBUG
        // can't render debug meshes in release
        [[discard]] doc->RemoveChild(doc->GetElementById("showNav")->GetParentNode());
#endif
        
    }
    
    void PostTick(float d) final{
        deltaTime = d;
    }
};

struct NavApp : public App{
    void OnStartup(int argc, char** argv) final {        
        auto world = RavEngine::New<Level>();
        AddWorld(world);

        SetWindowTitle(VFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    
    void OnFatal(const std::string_view msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }

    bool NeedsAudio() const final {
        return false;
    }
};

START_APP(NavApp)
