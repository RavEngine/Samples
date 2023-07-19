#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include "AppInfo.hpp"
#include "Flagpole.hpp"
#include <RavEngine/GUI.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/RenderEngine.hpp>

using namespace RavEngine;
using namespace std;

struct GrassMatUniforms {
    float time = 0;
};

struct GrassMat : public RavEngine::Material {
    GrassMat() : Material("grass", RavEngine::MaterialConfig{
        .vertConfig = RavEngine::defaultVertexConfig,
            .colorBlendConfig = RavEngine::defaultColorBlendConfig,
            .bindings = {
                {
                    .binding = 2,
                    .type = RGL::BindingType::StorageBuffer,
                    .stageFlags = RGL::BindingVisibility::Vertex
                }
        },
            .pushConstantSize = sizeof(GrassMatUniforms)
    }) {}
};

struct GrassMatInst : public RavEngine::MaterialInstance {
    GrassMatInst(Ref<GrassMat> f) : MaterialInstance(f) {}
    void SetTime(float time) {
        pushConstantData.time = time;
    }
    virtual const RGL::untyped_span GetPushConstantData() const override {
        return pushConstantData;
    }
private:
    GrassMatUniforms pushConstantData;
};

struct Level : public World{
    
    float deltaTime = 0;
    
    float cameraSpeed = 0.02;
    float cameraZoomSpeed = 0.07;
    
    GameObject cameraRoot = CreatePrototype<GameObject>();
    GameObject cameraGimball = CreatePrototype<GameObject>();
    GameObject cameraEntity;

    Flagpole flagpole;
    Ref<GrassMatInst> grassMatInst;
    
    void CameraLR(float amt){
        cameraRoot.GetTransform().LocalRotateDelta(vector3(0,amt * deltaTime * cameraSpeed,0));
    }
    
    void CameraUD(float amt){
        cameraGimball.GetTransform().LocalRotateDelta(vector3(-amt * deltaTime * cameraSpeed,0,0));
    }

    void CameraZoom(float amt) {
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0, 0, amt * deltaTime * cameraZoomSpeed));
    }

    void PreTick(float fpsScale) override {
        auto time = GetApp()->GetCurrentTime();
        std::static_pointer_cast<FlagMatInst>(flagpole.GetCurrentMaterial())->SetTime(time);
        grassMatInst->SetTime(time);
    }
    
    Level(){
        cameraEntity = CreatePrototype<GameObject>();
        auto& camera = cameraEntity.EmplaceComponent<CameraComponent>();
        camera.SetActive(true);
        cameraEntity.GetTransform().LocalTranslateDelta(vector3(0,0,10));
        
        cameraRoot.GetTransform().AddChild(cameraGimball);
        cameraGimball.GetTransform().AddChild(cameraEntity);
        cameraRoot.GetTransform().LocalTranslateDelta(vector3(0,5,0));
        
        auto lightEntity = CreatePrototype<GameObject>();
        lightEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
        lightEntity.EmplaceComponent<DirectionalLight>().SetCastsShadows(true);
        lightEntity.GetTransform().LocalRotateDelta(vector3(PI/4,PI/4,PI/3));
        
        auto guiEntity = CreatePrototype<GameObject>();
        auto& gui = guiEntity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");

        // generate grass blades
        {
			constexpr int nblades = 4096;
			constexpr float scale = 0.3;
			auto grassmesh = MeshAsset::Manager::Get("grass.obj");
			grassMatInst = RavEngine::New<GrassMatInst>(Material::Manager::Get<GrassMat>());
			
			for (int i = 0; i < nblades; i++) {
				auto grassEntity = CreatePrototype<GameObject>();
				auto& mesh = grassEntity.EmplaceComponent<StaticMesh>(grassmesh,grassMatInst);

				auto& transform = grassEntity.GetTransform();

				transform.SetLocalPosition({Random::get(-10.0,10.0), 0, Random::get(-10.0, 10.0)});
				transform.SetWorldRotation(vector3{0,Random::get(-0.75f,0.75f),0});
				transform.SetLocalScale({Random::get(scale, scale * 2), Random::get(scale * 0.3, scale * 1.6), scale});
			}
        }
        
        ComponentHandle<GUIComponent> gh(guiEntity);
        auto im = GetApp()->inputManager = RavEngine::New<InputManager>();
        im->AddAxisMap("MouseX", Special::MOUSEMOVE_X);
        im->AddAxisMap("MouseY", Special::MOUSEMOVE_Y);
        im->BindAxis("MouseX", gh, &GUIComponent::MouseX, CID::ANY);
        im->BindAxis("MouseY", gh, &GUIComponent::MouseY, CID::ANY);
        im->BindAnyAction(gh->GetData());
        
        im->AddAxisMap("CUD", SDL_SCANCODE_W);
        im->AddAxisMap("CUD", SDL_SCANCODE_S,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_A,-1);
        im->AddAxisMap("CLR", SDL_SCANCODE_D);
        im->AddAxisMap("CZ", SDL_SCANCODE_UP,-1);
        im->AddAxisMap("CZ", SDL_SCANCODE_DOWN);

        
        im->BindAxis("CUD", GetInput(this), &Level::CameraUD, CID::ANY);
        im->BindAxis("CLR", GetInput(this), &Level::CameraLR, CID::ANY);
        im->BindAxis("CZ", GetInput(this), &Level::CameraZoom, CID::ANY);
        
        auto ground = CreatePrototype<GameObject>();
        auto groundMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        groundMat->SetAlbedoColor({ 92/255.f, 60/255.f, 29/255.f,1});
        ground.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("quad.obj"),groundMat);
        ground.GetTransform().LocalScaleDelta(vector3(10));
        
        flagpole = CreatePrototype<Flagpole>();
        
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
    void OnStartup(int argc, char** argv) final {
        AddWorld(RavEngine::New<Level>());

        SetWindowTitle(RavEngine::StrFormat("{} | {}", APPNAME, GetRenderEngine().GetCurrentBackendName()).c_str());
    }
    void OnFatal(const char* msg) final{
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, RavEngine::Dialog::MessageBoxType::Error);
    }
};

START_APP(FlagsApp)
