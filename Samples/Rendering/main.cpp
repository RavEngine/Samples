#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/InputManager.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioSpace.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/BuiltinPostProcess.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/ParticleEmitter.hpp>
#include <RavEngine/ParticleMaterial.hpp>
#include "AppInfo.hpp"
#include <numbers>
#include <RavEngine/StartApp.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;
using namespace std;


struct RenderingApp : public RavEngine::App {
    void OnStartup(int argc, char** argv) final;
    void OnFatal(const std::string_view msg) final {
        RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
    }
    bool NeedsAudio() const final {
        return false;
    }
};

struct SmokeParticleUpdateMaterial : public ParticleUpdateMaterial {
    SmokeParticleUpdateMaterial() : ParticleUpdateMaterial("SmokeParticleInit", "SmokeParticleUpdate") {};
};


struct FireParticleUpdateMaterial : public ParticleUpdateMaterial {
    FireParticleUpdateMaterial() : ParticleUpdateMaterial("FireParticleInit", "FireParticleUpdate") {}
};

struct AsteroidUpdateMaterial : public ParticleUpdateMaterial {
    AsteroidUpdateMaterial() : ParticleUpdateMaterial("AsteroidInit", "AsteroidUpdate") {}
};

struct Level : public RavEngine::World {

    GameObject camRoot, camHeadUD;
    float camSpeed = 0.05;
    constexpr static float camTurnSpeed = 0.003;

    decimalType fsScale = 0;
    vector3 velvec{ 0,0,0 };
    bool relativeMouseMode = true;

    constexpr static vector3 cameraResetPos = vector3(0,5,10);

    struct StarMatPushConstants{
        float applicationTime = 0;
    };
    
    struct StarMat : public RavEngine::UnlitMaterial{
        StarMat() : UnlitMaterial("star", {
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

    struct FlameTag {};
    
    Ref<StarMatMaterialInstance> starMaterialInstance;
    ComponentHandle<ParticleEmitter> smokeParticle;
    
    Level() {

        constexpr static float floorSize = 20;
        auto floor = Instantiate<GameObject>();
        floor.GetTransform().SetLocalScale(vector3(floorSize, 1, floorSize));

        auto floorMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("quad.obj"));
        auto floorMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        floorMat->SetAlbedoColor({ 0.5,0.5,0.5,1 });
        floor.EmplaceComponent<StaticMesh>(floorMesh, floorMat);
        

        // asteroids
        auto asteroidMeshCol = New<MeshCollectionStatic>(std::initializer_list<MeshCollectionStatic::Entry>{
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod0.obj"),
                .minDistance = 0
            },
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod1.obj"),
                .minDistance = 40,
            },
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod2.obj"),
                .minDistance = 60,
            },
        });
        for (int i = 0; i < 100; i++) {
            auto asteroid = Instantiate<GameObject>();
            asteroid.EmplaceComponent<StaticMesh>(asteroidMeshCol, floorMat);
            auto pos = vector3(std::sin(Random::get(0.f, 2*3.14f)),Random::get(0.f, 1.f), std::cos(Random::get(0.f, 2 * 3.14f))) * Random::get(50.f, 80.f);
            asteroid.GetTransform().SetWorldPosition(pos);
        }
    
        camRoot = Instantiate<decltype(camRoot)>();
        camHeadUD = Instantiate<decltype(camHeadUD)>();
        camRoot.GetTransform().AddChild(camHeadUD);
        
        camRoot.GetTransform().SetWorldPosition(cameraResetPos);

        auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
        cam.SetActive(true);

        auto lightsEntity = Instantiate<GameObject>();
        auto& light = lightsEntity.EmplaceComponent<DirectionalLight>();
        light.SetIntensity(4);
        light.SetCastsShadows(true);
        lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
       

        lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });

        auto smokeParticleEntity = Instantiate<GameObject>();
        auto smokeParticleRenderMat = New<SpritesheetParticleRenderMaterial<LightingMode::Lit>>();


        struct alignas(4) ParticleRenderData {
            glm::vec3 pos;
            glm::vec2 scale;
            uint32_t animationFrame;
        };

        auto smokeRenderMat = RavEngine::New<SpritesheetParticleRenderMaterialInstance>(smokeParticleRenderMat, sizeof(ParticleRenderData), 0, offsetof(ParticleRenderData,scale), offsetof(ParticleRenderData, animationFrame));
        smokeRenderMat->SetSpritesheet(Texture::Manager::Get("smoke.png"));
        smokeRenderMat->spriteDim = {
            .numSpritesWidth = 3,
            .numSpritesHeight = 3
        };

        auto smokeUpdateMat = New<ParticleUpdateMaterialInstance>(New<SmokeParticleUpdateMaterial>());

        auto& smokeEmitter = smokeParticleEntity.EmplaceComponent<ParticleEmitter>(8192, sizeof(ParticleRenderData), smokeUpdateMat, smokeRenderMat); // number of particles we want
        //smokeEmitter.mode = ParticleEmitter::Mode::Burst;
        smokeEmitter.Play();
        smokeParticle = { smokeParticleEntity };
        smokeEmitter.SetEmissionRate(1000);
        smokeParticleEntity.EmplaceComponent<FlameTag>();

        auto fireParticleEntity = Instantiate<GameObject>();
        auto fireParticleRenderMat = New<SpritesheetParticleRenderMaterial<LightingMode::Unlit>>();
        auto fireRenderMat = RavEngine::New<SpritesheetParticleRenderMaterialInstance>(fireParticleRenderMat, sizeof(ParticleRenderData), 0, offsetof(ParticleRenderData, scale), offsetof(ParticleRenderData, animationFrame));
        fireRenderMat->SetSpritesheet(Texture::Manager::Get("fire.png"));
        fireRenderMat->spriteDim = {
            .numSpritesWidth = 11,
            .numSpritesHeight = 1
        };
        auto fireUpdateMat = New<ParticleUpdateMaterialInstance>(New<FireParticleUpdateMaterial>());
        auto& fireEmitter = fireParticleEntity.EmplaceComponent<ParticleEmitter>(8192, sizeof(ParticleRenderData), fireUpdateMat, fireRenderMat);
        fireEmitter.SetCastsShadows(false);
        fireEmitter.Play();
        fireEmitter.SetEmissionRate(1000);
        fireParticleEntity.EmplaceComponent<FlameTag>();
#if 1
        struct AsteroidParticleData {
            glm::quat rot;
            glm::vec3 pos;
            glm::vec3 scale;
            glm::vec3 velocity;
        };

        auto asteroidUpdateMat = New<ParticleUpdateMaterialInstance>(New<AsteroidUpdateMaterial>());
        auto asteroidSelectionMat = New<MeshParticleMeshSelectionMaterialInstance>(New<MeshParticleMeshSelectionMaterial>("AsteroidMeshSelection"));
        auto asteroidRenderMat = New<PBRMeshParticleRenderMaterialInstance>(New<PBRMeshParticleRenderMaterial>(),asteroidMeshCol, sizeof(AsteroidParticleData), offsetof(AsteroidParticleData,pos), offsetof(AsteroidParticleData, scale), offsetof(AsteroidParticleData, rot));

        asteroidRenderMat->SetMeshSelectionFunction(asteroidSelectionMat);

        auto asteroidEmitterEntity = Instantiate<GameObject>();
        auto& emitter = asteroidEmitterEntity.EmplaceComponent<ParticleEmitter>(1024, sizeof(AsteroidParticleData), asteroidUpdateMat, asteroidRenderMat);
        asteroidEmitterEntity.GetTransform().LocalTranslateDelta({0,2,0});
        emitter.Play();
        emitter.SetEmissionRate(50);
#endif

        SetupInputs();

        constexpr auto MoveParticleSystem = [](const ParticleEmitter& emitter, const FlameTag& ft, Transform& t) {
            auto time = GetApp()->GetCurrentTime();
            t.SetLocalPosition({ std::sin(time) * 5, 0, 0 });
        };
        EmplaceSystem<decltype(MoveParticleSystem)>();      
        
        // create the scene
        
        auto helmetObj = Instantiate<GameObject>();
        auto helmetMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("helmet.obj"));
        auto helmetMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        helmetMat->SetAlbedoTexture(Texture::Manager::Get("Default_albedo.png"));
        helmetMat->SetNormalTexture(Texture::Manager::Get("Default_normal.png"));
        helmetMat->SetMetallicTexture(Texture::Manager::Get("Default_metalness.png"));
        helmetMat->SetRoughnessTexture(Texture::Manager::Get("Default_roughness.png"));
        helmetMat->SetAOTexture(Texture::Manager::Get("Default_AO.png"));
        
        helmetObj.EmplaceComponent<StaticMesh>(helmetMesh, helmetMat);
        
        auto objectDistance = 5;
        
        helmetObj.GetTransform().LocalTranslateDelta({-objectDistance,5,0}).LocalScaleDelta(vector3(2.0f));
        
        // the unlit material
        auto star = Instantiate<GameObject>();
        auto starMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("sphere.obj"));
        starMaterialInstance = New<StarMatMaterialInstance>(Material::Manager::Get<StarMat>());
        star.EmplaceComponent<StaticMesh>(starMesh, starMaterialInstance);
        star.GetTransform().LocalTranslateDelta({objectDistance,5,0});
        
        // post procesing
        auto& globalEffects = GetApp()->GetRenderEngine().globalEffects.effects;

        auto fxaaEffectInstance = New<FXAAEffect>();
        auto bloomEffectInstance = New<BloomEffect>();

        globalEffects.push_back(fxaaEffectInstance);
        globalEffects.push_back(bloomEffectInstance);
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
            * ResetCamera = "ResetCam",
            * ChangeSpeed = "ChangeSpeed",
            * PlayParticle = "PlayParticle"
            ;
    };

    void CamChangeSpeed(float val){
        if (val > 0) {
            camSpeed = std::max(camSpeed - 0.05f, 0.f);
        }
        else if (val < 0) {
            camSpeed += 0.05f;
        }
    }

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
        im->AddAxisMap(InputNames::ChangeSpeed, Special::MOUSEWHEEL_Y);

        im->AddActionMap(InputNames::PlayParticle, SDL_SCANCODE_P);
        im->AddActionMap(InputNames::ResetCamera, SDL_SCANCODE_RETURN);

        im->AddActionMap(InputNames::ToggleMouse, SDL_SCANCODE_ESCAPE);

        im->BindAxis(InputNames::MoveUp, GetInput(this), &Level::CamMoveY, CID::ANY);
        im->BindAxis(InputNames::MoveForward, GetInput(this), &Level::CamMoveFwd, CID::ANY);
        im->BindAxis(InputNames::MoveRight, GetInput(this), &Level::CamMoveStrafe, CID::ANY);
        im->BindAxis(InputNames::LookRight, GetInput(this), &Level::CamLookLR, CID::ANY);
        im->BindAxis(InputNames::LookUp, GetInput(this), &Level::CamLookUD, CID::ANY);
        im->BindAxis(InputNames::ChangeSpeed, GetInput(this), &Level::CamChangeSpeed, CID::ANY);

        im->BindAction(InputNames::ToggleMouse, GetInput(this), &Level::ToggleMouse, ActionState::Pressed, CID::ANY);
        im->BindAction(InputNames::ResetCamera, GetInput(this), &Level::CameraResetCallback, ActionState::Pressed, CID::ANY);
        im->SetRelativeMouseMode(relativeMouseMode);

        im->BindAction(InputNames::PlayParticle, GetInput(this), &Level::PlayParticle, ActionState::Pressed, CID::ANY);

        GetApp()->inputManager = im;
    }

    void PlayParticle() {
        smokeParticle->Reset();
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
