#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
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
                    auto vec = (otherPos - myPos) * (std::static_pointer_cast<RigidBodyDynamicComponent>(b)->GetMass() / 100);
                    body->AddForce(vec);
                }
            }
        }
    }
};

struct Level : public World{
    inline void init(){
        
        // lighting and cameras
        auto lightcam = Entity::New();
        lightcam->EmplaceComponent<AmbientLight>()->Intensity = 0.5;
        lightcam->EmplaceComponent<CameraComponent>()->SetActive(true);
        lightcam->GetTransform()->LocalRotateDelta(vector3(-PI/2,0,0));
        lightcam->GetTransform()->WorldTranslateDelta(vector3(0,30,0));
        Spawn(lightcam);
        
        skybox.enabled = false;
        
        // the black hole
        auto blackhole = RavEngine::New<HeavyThing>(1000,0.2,ColorRGBA{0.1,0.1,0.1,1});
        Spawn(blackhole);
        
        Array<int,5> stars      {50,20,10,30,40};
        Array<int, 5> startDist {10,15, 4,12,20};
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
            star->GetComponent<RigidBodyDynamicComponent>().value()->SetLinearVelocity(vector3(10,0,0),true);
        }
       
        systemManager.EmplaceSystem<GravitySystem>(shared_from_this());
        InitPhysics();
    }
};

struct GravityApp : public App{
    GravityApp() : App(APPNAME){}
    void OnStartup(int argc, char** argv) final{
        auto level = RavEngine::New<Level>();
        level->init();
        AddWorld(level);
    }
};

START_APP(GravityApp)
