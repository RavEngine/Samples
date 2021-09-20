#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include "AppInfo.hpp"
#include "Flagpole.hpp"
using namespace RavEngine;
using namespace std;

struct Level : public World{
    void Init(){
        auto cameraEntity = Entity::New();
        auto camera = cameraEntity->EmplaceComponent<CameraComponent>();
        camera->SetActive(true);
        cameraEntity->GetTransform()->LocalTranslateDelta(vector3(0,5,10));
        
        auto lightEntity = Entity::New();
        lightEntity->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
        lightEntity->EmplaceComponent<DirectionalLight>();
        lightEntity->GetTransform()->LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto ground = Entity::New();
        ground->EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"),make_shared<PBRMaterialInstance>( Material::Manager::GetMaterial<PBRMaterial>()));
        ground->GetTransform()->LocalScaleDelta(vector3(10));
        
        auto flagpole = New<Flagpole>();
        
        Spawn(cameraEntity);
        Spawn(lightEntity);
        Spawn(ground);
        Spawn(flagpole);
    }
};

struct FlagsApp : public App{
    FlagsApp() : App(APPNAME) {}
    void OnStartup(int argc, char** argv) final {
        auto world = std::make_shared<Level>();
        world->Init();
        AddWorld(world);

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, Renderer->GetCurrentBackendName()).c_str());
    }
    
};

START_APP(FlagsApp)
