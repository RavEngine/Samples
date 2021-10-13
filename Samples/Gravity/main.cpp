#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
using namespace RavEngine;

struct HeavyThing : public Entity{
    HeavyThing(decimalType mass, float scaleOverride = 0.2, ColorRGBA colorOverride = {1,1,1,1}){
        auto body = EmplaceComponent<RigidBodyDynamicComponent>();
        body->SetGravityEnabled(false);
        body->SetMass(mass);
        MeshAssetOptions opt;
        opt.scale = scaleOverride;
        auto matinst = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        matinst->SetAlbedoColor(colorOverride);
        EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("sphere.obj",opt),matinst);
        if (mass < 1000){
            auto light = EmplaceComponent<PointLight>();
            light->Intensity = scaleOverride * 7;
            light->color = colorOverride;
        }
        else{
            auto light = EmplaceComponent<PointLight>();
            light->Intensity = 5;
            light->color = {1,1,1,1};
        }
    }
};

struct GravitySystem : public AutoCTTI{
    WeakRef<World> hostWorld;
    GravitySystem( decltype(hostWorld) w ) : hostWorld(w){}
    
    inline void Tick(float fpsScale, Ref<RigidBodyDynamicComponent> body) const{
        if(auto& otherBodies = hostWorld.lock()->GetAllComponentsOfType<RigidBodyDynamicComponent>()){
            auto myPos = body->GetOwner().lock()->GetTransform()->GetWorldPosition();
            for(const auto& b : otherBodies.value()){
                if (b != body){
                    // add a force corresponding to the mass of that other body
                    auto otherPos = b->GetOwner().lock()->GetTransform()->GetWorldPosition();
                    
                    // calculate M/r^2 * r^
                    auto r = glm::distance(otherPos, myPos);
                    auto rhat = glm::normalize(otherPos - myPos);
                    auto vec =(std::static_pointer_cast<RigidBodyDynamicComponent>(b)->GetMass()/(r*r)) * rhat;
                    body->AddForce(vec);
                }
            }
        }
    }
};

// controller names
struct Mappings{
    static constexpr char const
        * CameraUD = "CameraUD",
        * CameraLR = "CameraLR",
        * CameraZoom = "Zoom",
        * Reset = "Reset"
    ;
};

struct Level : public World{
    float currentScale = 0;
    float camSpeed = 1;
    
    inline Ref<Transform> getCameraTransform() const{
        return GetComponent<CameraComponent>().value()->GetOwner().lock()->GetTransform();
    }
    
    inline float scale(float amt){
        return amt * camSpeed * currentScale;
    }
    
    inline void MoveLR(float amt){
        getCameraTransform()->LocalTranslateDelta(vector3(scale(amt),0,0));
    }
    inline void MoveUD(float amt){
        getCameraTransform()->LocalTranslateDelta(vector3(0,0,scale(amt)));
    }
    inline void Zoom(float amt){
        getCameraTransform()->LocalTranslateDelta(vector3(0,scale(amt),0));
    }
    inline void Reset(){
        MoveToDefault( getCameraTransform());
    }
    inline void MoveToDefault(Ref<Transform> t) const{
        t->SetWorldPosition(vector3(0,100,0));
    }
    
    inline void init(){
        // lighting and cameras
        auto lightcam = Entity::New();
        lightcam->EmplaceComponent<AmbientLight>()->Intensity = 0.8;
        auto cam = lightcam->EmplaceComponent<CameraComponent>();
        cam->SetActive(true);
        cam->farClip = 1000;
        lightcam->GetTransform()->LocalRotateDelta(vector3(-PI/2,0,0));
        MoveToDefault(lightcam->GetTransform());
        auto gui = lightcam->EmplaceComponent<GUIComponent>();
        gui->AddDocument("main.rml");
        Spawn(lightcam);
        
        skybox.enabled = false;
        
        // the black hole (drawn as white for visibility)
        auto blackhole = RavEngine::New<HeavyThing>(50000,2,ColorRGBA{1,1,1,1});
        Spawn(blackhole);
        
        Array<int,5> stars      {50,20,10,30,40};
        Array<int, 5> startDist {20,30,40,50,60};
        Array<ColorRGBA, 5> colors{
            ColorRGBA{0,0.2,1,1},
            ColorRGBA{1,1,0,1},
            ColorRGBA{1,0,0,1},
            ColorRGBA{1,1,0,1},
            ColorRGBA{0,0.8,1,1}
        };
        
        for(int i = 0; i < stars.size(); i++){
            auto star = RavEngine::New<HeavyThing>(stars[i],stars[i]/50.0,colors[i]);
            star->GetTransform()->SetLocalPosition(vector3(0,0,startDist[i]));
            Spawn(star);
            star->GetComponent<RigidBodyDynamicComponent>().value()->SetLinearVelocity(vector3(5,0,0),true);
        }
       
        systemManager.EmplaceSystem<GravitySystem>(shared_from_this());
        InitPhysics();
        
        // setup input manager
        auto im = App::inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap(Mappings::CameraUD,SDL_SCANCODE_W,-1);
        im->AddAxisMap(Mappings::CameraUD,SDL_SCANCODE_S);
        im->AddAxisMap(Mappings::CameraLR, SDL_SCANCODE_A,-1);
        im->AddAxisMap(Mappings::CameraLR, SDL_SCANCODE_D);
        im->AddAxisMap(Mappings::CameraZoom, SDL_SCANCODE_UP,-1);
        im->AddAxisMap(Mappings::CameraZoom, SDL_SCANCODE_DOWN);
        im->AddActionMap(Mappings::Reset, SDL_SCANCODE_R);
        
        auto thisptr = std::static_pointer_cast<Level>(shared_from_this());
        im->BindAxis(Mappings::CameraUD, thisptr, &Level::MoveUD, CID::ANY);
        im->BindAxis(Mappings::CameraLR, thisptr, &Level::MoveLR, CID::ANY);
        im->BindAxis(Mappings::CameraZoom, thisptr, &Level::Zoom, CID::ANY);
        im->BindAction(Mappings::Reset, thisptr, &Level::Reset, ActionState::Pressed, CID::ANY);
    }
    
    void PreTick(float fpsScale) final {
        currentScale = fpsScale;
    }
};

struct GravityApp : public App{
    GravityApp() : App(APPNAME){}
    void OnStartup(int argc, char** argv) final{
        auto level = RavEngine::New<Level>();
        level->init();
        AddWorld(level);
        SetWindowTitle(StrFormat("RavEngine {} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
};

START_APP(GravityApp)
