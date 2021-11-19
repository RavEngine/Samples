#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include "AppInfo.hpp"
#include "Flagpole.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
using namespace RavEngine;
using namespace std;

struct Level : public World{
    
    float deltaTime = 0;
    
    float cameraSpeed = 0.02;
    
    GameObject cameraRoot = CreatePrototype<GameObject>();
    GameObject cameraGimball = CreatePrototype<GameObject>();
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }
    
    void Init(){
        auto cameraEntity = CreatePrototype<GameObject>();
        auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
        camera.SetActive(true);
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,0,10));
        
        cameraRoot.GetTransform().AddChild(ComponentHandle<Transform>(cameraGimball));
        cameraGimball.GetTransform().AddChild(ComponentHandle<Transform>(cameraEntity));
        cameraRoot.GetTransform().LocalTranslateDelta(vector3(0,5,0));
        
        auto lightEntity = CreatePrototype<GameObject>();
        lightEntity.EmplaceComponent<AmbientLight>().Intensity = 0.2;
        lightEntity.EmplaceComponent<DirectionalLight>();
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = CreatePrototype<GameObject>();
        auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        
        ComponentHandle<GUIComponent> gh(guiEntity);
        auto im = App::inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gh->GetData());
        
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);
        
        im->BindAxis("CUD", GetInput(this), &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", GetInput(this), &Level::CameraLR, CID::ANY);
        
        auto ground = CreatePrototype<GameObject>();
        ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"),make_shared<PBRMaterialInstance>( Material::Manager::Get<PBRMaterial>()));
        ground.GetTransform().LocalScaleDelta(vector3(10));
        
        auto flagpole = CreatePrototype<Flagpole>();
        
        auto picker = doc->GetElementById("picker");
        
        uint8_t flag_id = 0;
        for(const auto& f : flagpole.flags){
            auto opt = doc->CreateElement("option");
            opt->SetAttribute("value", StrFormat("{}",flag_id++));     // when creating options, we must assign them a value, otherwise the change event on the selector doesn't trigger if the option is selected
            opt->SetInnerRML(f.name);
            picker->AppendChild(std::move(opt));
        }
        
        struct changeListener : public Rml::EventListener{
            Flagpole pole;
            void ProcessEvent(Rml::Event& evt) final{
                auto selbox = static_cast<Rml::ElementFormControlSelect*>(evt.GetTargetElement());
                pole.SwitchToFlag(selbox->GetSelection());
            }
            changeListener(decltype(flagpole) fl ) : pole(fl){}
        };
        
       picker->AddEventListener(Rml::EventId::Change, new changeListener(flagpole));
    }
    
    void PostTick(float d) final{
        deltaTime = d;
    }
};

struct FlagsApp : public App{
    FlagsApp() : App(APPNAME) {}
    void OnStartup(int argc, char** argv) final {
        auto world = std::make_shared<Level>();
        world->Init();
        AddWorld(world);

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    
};

START_APP(FlagsApp)
