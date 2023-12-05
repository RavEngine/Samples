#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioRoom.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/BuiltinPostProcess.hpp>
#include <RavEngine/RenderEngine.hpp>
#include "AppInfo.hpp"
#include <numbers>

using namespace RavEngine;
using namespace std;

struct RenderingApp : public RavEngine::App {
    void OnStartup(int argc, char** argv) final;
    void OnFatal(const char* msg) final {
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
};


struct Level : public RavEngine::World {

    GameObject camRoot, camHeadUD;
    constexpr static float camSpeed = 0.005;
    constexpr static float camTurnSpeed = 0.003;

    decimalType fsScale = 0;
    vector3 velvec{ 0,0,0 };
    bool relativeMouseMode = true;

    constexpr static vector3 cameraResetPos = vector3(0,5,10);

    struct StarMatPushConstants{
        float applicationTime = 0;
    };
    
    struct StarMat : public RavEngine::Material{
        StarMat() : Material("star", RavEngine::MaterialConfig{
            .vertConfig = RavEngine::defaultVertexConfig,
            .colorBlendConfig = RavEngine::defaultUnlitColorBlendConfig,
            .pushConstantSize = sizeof(StarMatPushConstants),
        }){}
    };
    
    struct StarMatMaterialInstance : public RavEngine::MaterialInstance{
        StarMatMaterialInstance(Ref<StarMat> m) : MaterialInstance(m) { };
        StarMatPushConstants pushConstantData;
        virtual const RGL::untyped_span GetPushConstantData() const override {
            return pushConstantData;
        }
    };
    
    Ref<StarMatMaterialInstance> starMaterialInstance;
    
    Level() {

        constexpr static float floorSize = 20;
        auto floor = CreatePrototype<GameObject>();
        floor.GetTransform().SetLocalScale(vector3(floorSize, 1, floorSize));

        {
            auto floorMesh = MeshAsset::Manager::Get("quad.obj");
            auto floorMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
            floorMat->SetAlbedoColor({ 0.5,0.5,0.5,1 });
            floor.EmplaceComponent<StaticMesh>(floorMesh, LitMeshMaterialInstance(floorMat));
        }
    
        camRoot = CreatePrototype<decltype(camRoot)>();
        camHeadUD = CreatePrototype<decltype(camHeadUD)>();
        camRoot.GetTransform().AddChild(camHeadUD);
        
        camRoot.GetTransform().SetWorldPosition(cameraResetPos);

        auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
        cam.SetActive(true);

        auto lightsEntity = CreatePrototype<GameObject>();
        auto& light = lightsEntity.EmplaceComponent<DirectionalLight>();
        light.SetIntensity(4);
        light.SetCastsShadows(true);
        lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
       

        lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });

        SetupInputs();
        
        
        // create the scene
        
        auto helmetObj = CreatePrototype<GameObject>();
        auto helmetMesh = MeshAsset::Manager::Get("helmet.obj");
        auto helmetMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        helmetMat->SetAlbedoTexture(Texture::Manager::Get("Default_albedo.png"));
        helmetMat->SetNormalTexture(Texture::Manager::Get("Default_normal.png"));
        helmetMat->SetMetallicTexture(Texture::Manager::Get("Default_metalness.png"));
        helmetMat->SetRoughnessTexture(Texture::Manager::Get("Default_roughness.png"));
        helmetMat->SetAOTexture(Texture::Manager::Get("Default_AO.png"));
        
        helmetObj.EmplaceComponent<StaticMesh>(helmetMesh, LitMeshMaterialInstance(helmetMat));
        
        auto objectDistance = 5;
        
        helmetObj.GetTransform().LocalTranslateDelta({-objectDistance,5,0}).LocalScaleDelta(vector3(2.0f));
        
        // the unlit material
        auto star = CreatePrototype<GameObject>();
        auto starMesh = MeshAsset::Manager::Get("sphere.obj");
        starMaterialInstance = New<StarMatMaterialInstance>(Material::Manager::Get<StarMat>());
        star.EmplaceComponent<StaticMesh>(starMesh, UnlitMeshMaterialInstance(starMaterialInstance));
        star.GetTransform().LocalTranslateDelta({objectDistance,5,0});
        
        // post procesing
        auto bloomEffect = New<BloomEffect>();
        auto bloomEffectInstance = New<BloomEffectInstance>(bloomEffect);
        
        GetApp()->GetRenderEngine().globalEffects.effects.push_back(bloomEffectInstance);
    }

    
    void CameraResetCallback() {
        camRoot.GetTransform().SetWorldPosition(cameraResetPos).SetWorldRotation(vector3(0,0,0));
    }

    struct InputNames {
        static constexpr char const
            * MoveForward = "MoveForward",
            * MoveRight = "MoveRight",
            * MoveUp = "MoveUp",
            * LookRight = "LookRight",
            * LookUp = "LookUp",
            * ToggleMouse = "ToggleMouse",
            * ResetCamera = "ResetCam"
            ;
    };

    void CamMoveY(float amt) {
        velvec.y += amt * camSpeed * fsScale;
    }

    void CamMoveFwd(float amt) {
        velvec += camRoot.GetTransform().Forward() * amt * camSpeed * fsScale;
    }

    void CamMoveStrafe(float amt) {
        velvec += camRoot.GetTransform().Right() * amt * camSpeed * fsScale;
    }

    void CamLookLR(float amt) {
        if (relativeMouseMode) {
            camRoot.GetTransform().LocalRotateDelta(vector3(0, amt * camTurnSpeed * fsScale, 0));
        }
    }

    void CamLookUD(float amt) {
        if (relativeMouseMode) {
            camHeadUD.GetTransform().LocalRotateDelta(vector3(amt * camTurnSpeed * fsScale, 0, 0));
        }
    }

    void ToggleMouse() {
        relativeMouseMode = !relativeMouseMode;
        GetApp()->inputManager->SetRelativeMouseMode(relativeMouseMode);
    }

    void SetupInputs() {
        auto im = New<InputManager>();
        im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_SPACE);
        im->AddAxisMap(InputNames::MoveUp, SDL_SCANCODE_LSHIFT, -1);
        im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_W);
        im->AddAxisMap(InputNames::MoveForward, SDL_SCANCODE_S, -1);
        im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_A, -1);
        im->AddAxisMap(InputNames::MoveRight, SDL_SCANCODE_D);
        im->AddAxisMap(InputNames::LookRight, Special::MOUSEMOVE_XVEL, -1);
        im->AddAxisMap(InputNames::LookUp, Special::MOUSEMOVE_YVEL, -1);
        im->AddActionMap(InputNames::ResetCamera, SDL_SCANCODE_RETURN);

        im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

        im->BindAxis(InputNames::MoveUp, GetInput(this), &Level::CamMoveY, CID::ANY);
        im->BindAxis(InputNames::MoveForward, GetInput(this), &Level::CamMoveFwd, CID::ANY);
        im->BindAxis(InputNames::MoveRight, GetInput(this), &Level::CamMoveStrafe, CID::ANY);
        im->BindAxis(InputNames::LookRight, GetInput(this), &Level::CamLookLR, CID::ANY);
        im->BindAxis(InputNames::LookUp, GetInput(this), &Level::CamLookUD, CID::ANY);

        im->BindAction(InputNames::ToggleMouse, GetInput(this), &Level::ToggleMouse, ActionState::Pressed, CID::ANY);
        im->BindAction(InputNames::ResetCamera, GetInput(this), &Level::CameraResetCallback, ActionState::Pressed, CID::ANY);
        im->SetRelativeMouseMode(relativeMouseMode);

        GetApp()->inputManager = im;
    }

    void PreTick(float scale) final {
        fsScale = scale;
        starMaterialInstance->pushConstantData.applicationTime = GetApp()->GetCurrentTime();
    }

    void PostTick(float tickrateScale) final {
        camRoot.GetTransform().LocalTranslateDelta(velvec);
        velvec *= 0.9;

        auto now = GetApp()->GetCurrentTime();
    }
};

void RenderingApp::OnStartup(int argc, char** argv) {

    SetWindowTitle(APPNAME);

    auto level = RavEngine::New<Level>();

    AddWorld(level);
}

START_APP(RenderingApp)
