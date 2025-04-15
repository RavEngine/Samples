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
#include <RavEngine/Window.hpp>
#include <RavEngine/MeshCollection.hpp>
#include <RavEngine/BuiltinTonemap.hpp>

using namespace RavEngine;
using namespace std;

// Metal bug on x86 macOS prevents transparency from working
#define ENABLE_TRANSPARENTS !(__APPLE__ && __x86_64__)
#define ENABLE_OPAQUES 1
#define ENABLE_PARTICLES 1

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

struct AsteroidUBO {
    uint32_t bytesPerParticle;
    uint32_t positionOffset;
    uint32_t scaleOffset;
    uint32_t rotationOffset;
    uint32_t alphaOffset;
};

struct AsteroidParticleData {
    glm::vec4 rot;
    glm::vec3 pos;
    glm::vec3 scale;
    glm::vec3 velocity;
    float alpha;
};

struct AsteroidRenderMaterial : public MeshParticleRenderMaterial<LightingMode::Lit> {
    AsteroidRenderMaterial() : MeshParticleRenderMaterial("AsteroidRender", "AsteroidRender", {.pushConstantSize = sizeof(AsteroidUBO), .opacityMode = OpacityMode::Transparent}) {}
};

struct AsteroidRenderMaterialInstance : public MeshParticleRenderMaterialInstance {
    AsteroidRenderMaterialInstance(Ref<AsteroidRenderMaterial> m, Ref<MeshCollectionStatic> meshes) : MeshParticleRenderMaterialInstance(Ref<MeshParticleRenderMaterial<LightingMode::Lit>>(m),meshes) {}

    uint8_t SetPushConstantData(std::span<std::byte, 128> data) const override {
        constexpr static AsteroidUBO ubo{
            .bytesPerParticle = sizeof(AsteroidParticleData),
            .positionOffset = offsetof(AsteroidParticleData,pos),
            .scaleOffset = offsetof(AsteroidParticleData,scale),
            .rotationOffset = offsetof(AsteroidParticleData,rot),
            .alphaOffset = offsetof(AsteroidParticleData,alpha)
        };

        std::memcpy(data.data(), &ubo, sizeof(ubo));

        return sizeof(ubo);
    }
};

struct GlassMat : public LitMaterial {
    GlassMat() : LitMaterial("pbr", "wineglass", 
        {
            
        }, 
        {
            .cullMode = RGL::CullMode::None,
            .opacityMode = OpacityMode::Transparent
        }) {}
};

struct GlassMatInstance : public MaterialInstance {
    constexpr static uint32_t priority = 2;
    GlassMatInstance(Ref<GlassMat> m) : MaterialInstance(m, priority) {}
};

struct BakedMat : public LitMaterial {
    BakedMat() : LitMaterial("bakedlight", PipelineOptions{}, { .requiredAttributes = {
        .position = true,
        .normal = true,
        .tangent = true,
        .bitangent = true,
        .uv0 = true,
        .lightmapUV = true
        } }) {}
};

struct BakedMatInstance : public MaterialInstance {
    BakedMatInstance(Ref<BakedMat> m) : MaterialInstance(m) {}
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

    struct TQuadMat : public UnlitMaterial {
        TQuadMat() : UnlitMaterial("unlit_transparent", {}, {
            .cullMode = RGL::CullMode::None,
            .opacityMode = OpacityMode::Transparent
        }) {}
    };

    struct TQuadMatInstance : public MaterialInstance {
        constexpr static uint32_t priority = 1;
        TQuadMatInstance(Ref<TQuadMat>m) : MaterialInstance(m,priority) {}
    };

    struct alignas(4) ParticleRenderData {
        glm::vec3 pos;
        glm::vec2 scale;
        uint32_t animationFrame;
    };

    struct FireParticleDataUBO {
        ParticleBillboardUBO innerUbo;
        uint32_t particleAlphaOffset;
    };

    struct FireParticleMaterial : public SpritesheetParticleRenderMaterial<LightingMode::Unlit>{
        FireParticleMaterial() : SpritesheetParticleRenderMaterial("FireParticleRender","FireParticleRender", OpacityMode::Transparent, sizeof(FireParticleDataUBO)) {}
    };

    struct FireParticleRenderData {
        ParticleRenderData innerData;
        float alpha;
    };

    struct FireParticleMaterialInstance : public SpritesheetParticleRenderMaterialInstance {

        FireParticleMaterialInstance(Ref<FireParticleMaterial> m, uint32_t alphaOffset) : SpritesheetParticleRenderMaterialInstance(Ref<SpritesheetParticleRenderMaterial<LightingMode::Unlit>>(m),
            sizeof(FireParticleRenderData), 0, offsetof(FireParticleRenderData, innerData.scale), offsetof(FireParticleRenderData, innerData.animationFrame)) {
            this->alphaOffset = alphaOffset;
        }

        uint32_t alphaOffset;

        uint8_t SetPushConstantData(std::span<std::byte, 128> data) const {
            SpritesheetParticleRenderMaterialInstance::SetPushConstantData(data);
            struct fireUBO {
                ParticleBillboardUBO inner;
                uint32_t alphaOffset;
            };
            std::memcpy(data.data() + offsetof(fireUBO, alphaOffset), &alphaOffset, sizeof(alphaOffset));

            return sizeof(fireUBO);
        }
    };

    struct FlameTag {};
    
    Ref<StarMatMaterialInstance> starMaterialInstance;
    ComponentHandle<ParticleEmitter> smokeParticle;
    
    Level() {
        constexpr static renderlayer_t bakedLayer = 0b01;
        auto floorMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("quad"));
        auto asteroidMeshCol = New<MeshCollectionStatic>(std::initializer_list<MeshCollectionStatic::Entry>{
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod0"),
                .minDistance = 0
            },
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod1"),
                .minDistance = 40,
            },
            {
                .mesh = MeshAsset::Manager::Get("asteroid_lod2"),
                .minDistance = 60,
            },
        });
#if ENABLE_OPAQUES
        constexpr static float floorSize = 20;
        auto floor = Instantiate<GameObject>();
        floor.GetTransform().SetLocalScale(vector3(floorSize, 1, floorSize));

        auto floorMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>(),2);
        floorMat->SetAlbedoColor({ 0.5,0.5,0.5,1 });
        floor.EmplaceComponent<StaticMesh>(floorMesh, floorMat);
        

        // asteroids
        for (int i = 0; i < 100; i++) {
            auto asteroid = Instantiate<GameObject>();
            asteroid.EmplaceComponent<StaticMesh>(asteroidMeshCol, floorMat);
            auto pos = vector3(std::sin(Random::get(0.f, 2*3.14f)),Random::get(0.f, 1.f), std::cos(Random::get(0.f, 2 * 3.14f))) * Random::get(50.f, 80.f);
            asteroid.GetTransform().SetWorldPosition(pos);
        }

        // baked lighting demo
        {
            auto bakedMat = RavEngine::New<PBRMaterialBakedInstance>(Material::Manager::Get<PBRMaterialBaked>());
            auto lightmapTex = Texture::Manager::Get("bakedshadow.png");
            bakedMat->SetBakedShadowTexture(lightmapTex);

            auto bakedCubeObj = Instantiate<GameObject>();
            bakedCubeObj.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("bakedcube"), bakedMat);
            auto& cubeTransform = bakedCubeObj.GetTransform();
            cubeTransform.SetLocalPosition({-20,1,0});

            auto bakedPlaneObj = Instantiate<GameObject>();
            bakedPlaneObj.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("bakedplane"), bakedMat);
            auto& planeTransform = bakedPlaneObj.GetTransform();
            planeTransform.SetLocalPosition({ -20,1,0 });

        }

        // environment lighting demo 
        {
            auto shinyMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
            shinyMat->SetMetallicTint(0.9);
            shinyMat->SetRoughnessTint(0.1);
            shinyMat->SetSpecularTint(0.8);

            auto shinyObject = Instantiate<GameObject>();
            shinyObject.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("sphere"), shinyMat);
            shinyObject.GetTransform().SetWorldPosition({ -2, 2, 12});
        }
#endif

        // wine glasses
#if ENABLE_TRANSPARENTS
        auto wineglassMeshCol = MeshCollectionStaticManager::Get("wineglass");
        auto glassMat = New<GlassMatInstance>(New<GlassMat>());
        for (int i = 0; i < 100; i++) {
            auto glass = Instantiate<GameObject>();
            glass.EmplaceComponent<StaticMesh>(wineglassMeshCol, glassMat);

            vector3 pos = vector3(i % 10, 0, i / 10) * 2.f;

            glass.GetTransform().SetWorldPosition(pos);
        }

        // unlit transparent quads
        auto tquadMat = New< TQuadMatInstance>(New<TQuadMat>());
        for (int i = 0; i < 10; i++) {
            auto obj = Instantiate<GameObject>();
            obj.EmplaceComponent<StaticMesh>(floorMesh, tquadMat);

            obj.GetTransform().SetWorldPosition({-10, 2, i});
            obj.GetTransform().SetWorldRotation(vector3{PI / 2,0,0});
        }
#endif
    
        camRoot = Instantiate<decltype(camRoot)>();
        camHeadUD = Instantiate<decltype(camHeadUD)>();
        camRoot.GetTransform().AddChild(camHeadUD);
        
        camRoot.GetTransform().SetWorldPosition(cameraResetPos);

        auto& cam = camHeadUD.EmplaceComponent<CameraComponent>();
        cam.SetActive(true);
        // post procesing
        auto& camEffects = cam.postProcessingEffects.effects;

        camEffects.push_back(std::make_unique<FXAAEffect>());
        camEffects.push_back(std::make_unique<BloomEffect>());

        auto lightsEntity = Instantiate<GameObject>();
        auto& light = lightsEntity.EmplaceComponent<DirectionalLight>();
        light.SetIntensity(4);
        light.SetCastsShadows(true);
        light.SetIlluminationLayers(~bakedLayer);
        auto& ambientLight = lightsEntity.EmplaceComponent<AmbientLight>();
        ambientLight.SetIntensity(0.2);
        ambientLight.SetIlluminationLayers(~bakedLayer);
        CubemapTexture::Config envConfig;
        envConfig.debugName = "Environment map";
        envConfig.format = RGL::TextureFormat::RGBA16_Sfloat;
        envConfig.numMips = 4;
        envConfig.enableRenderTarget = true;
        auto envCubemap = RavEngine::New<CubemapTexture>(512, envConfig);
        
        envConfig.debugName = "Irradiance map";
        envConfig.numMips = 1;
        auto irradianceCubemap = RavEngine::New<CubemapTexture>(512, envConfig);
        ambientLight.environment.emplace(skybox, envCubemap, irradianceCubemap);
       

        lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });

        auto smokeParticleEntity = Instantiate<GameObject>();
        auto smokeParticleRenderMat = New<SpritesheetParticleRenderMaterial<LightingMode::Lit>>();


        auto smokeRenderMat = RavEngine::New<SpritesheetParticleRenderMaterialInstance>(smokeParticleRenderMat, sizeof(ParticleRenderData), 0, offsetof(ParticleRenderData,scale), offsetof(ParticleRenderData, animationFrame));
        smokeRenderMat->SetSpritesheet(Texture::Manager::Get("smoke.png"));
        smokeRenderMat->spriteDim = {
            .numSpritesWidth = 3,
            .numSpritesHeight = 3
        };

        auto smokeUpdateMat = New<ParticleUpdateMaterialInstance>(New<SmokeParticleUpdateMaterial>());
#if ENABLE_PARTICLES
#if ENABLE_OPAQUES
        auto& smokeEmitter = smokeParticleEntity.EmplaceComponent<ParticleEmitter>(8192, sizeof(ParticleRenderData), smokeUpdateMat, smokeRenderMat); // number of particles we want
        //smokeEmitter.mode = ParticleEmitter::Mode::Burst;
        smokeEmitter.Play();
        smokeParticle = { smokeParticleEntity };
        smokeEmitter.SetEmissionRate(1000);
        smokeParticleEntity.EmplaceComponent<FlameTag>();
#endif
#if ENABLE_TRANSPARENTS
        auto fireParticleEntity = Instantiate<GameObject>();
        auto fireParticleRenderMat = New<FireParticleMaterial>();
        auto fireRenderMat = RavEngine::New<FireParticleMaterialInstance>(fireParticleRenderMat, offsetof(FireParticleRenderData, alpha));
        fireRenderMat->SetSpritesheet(Texture::Manager::Get("fire.png"));
        fireRenderMat->spriteDim = {
            .numSpritesWidth = 11,
            .numSpritesHeight = 1
        };
        auto fireUpdateMat = New<ParticleUpdateMaterialInstance>(New<FireParticleUpdateMaterial>());
        auto& fireEmitter = fireParticleEntity.EmplaceComponent<ParticleEmitter>(8192, sizeof(ParticleRenderData), fireUpdateMat, fireRenderMat);

        fireParticleEntity.SetEntityAttributes(fireParticleEntity.GetEntityAttributes() & ~CastsShadowsBit);
        fireEmitter.Play();
        fireEmitter.SetEmissionRate(1000);
        fireParticleEntity.EmplaceComponent<FlameTag>();

        auto asteroidUpdateMat = New<ParticleUpdateMaterialInstance>(New<AsteroidUpdateMaterial>());
        auto asteroidSelectionMat = New<MeshParticleMeshSelectionMaterialInstance>(New<MeshParticleMeshSelectionMaterial>("AsteroidMeshSelection"));
        auto asteroidRenderMat = New<AsteroidRenderMaterialInstance>(New<AsteroidRenderMaterial>(),asteroidMeshCol);

        asteroidRenderMat->SetMeshSelectionFunction(asteroidSelectionMat);

        auto asteroidEmitterEntity = Instantiate<GameObject>();
        auto& emitter = asteroidEmitterEntity.EmplaceComponent<ParticleEmitter>(1024, sizeof(AsteroidParticleData), asteroidUpdateMat, asteroidRenderMat);
        asteroidEmitterEntity.GetTransform().LocalTranslateDelta({0,2,0});
        emitter.Play();
        emitter.SetEmissionRate(50);
#endif
#endif

        SetupInputs();
#if ENABLE_PARTICLES
        constexpr auto MoveParticleSystem = [](const ParticleEmitter& emitter, const FlameTag& ft, Transform& t) {
            auto time = GetApp()->GetCurrentTime();
            t.SetLocalPosition({ std::sin(time) * 5, 0, 0 });
        };
        EmplaceSystem<decltype(MoveParticleSystem)>();
#endif
        
        // create the scene
#if ENABLE_OPAQUES
        auto helmetObj = Instantiate<GameObject>();
        auto helmetMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("helmet"));
        auto helmetMat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>(),1);
        helmetMat->SetAlbedoTexture(Texture::Manager::Get("Default_albedo.png"));
        helmetMat->SetNormalTexture(Texture::Manager::Get("Default_normal.png"));
        helmetMat->SetMetallicTexture(Texture::Manager::Get("Default_metalness.png"));
        helmetMat->SetRoughnessTexture(Texture::Manager::Get("Default_roughness.png"));
        helmetMat->SetAOTexture(Texture::Manager::Get("Default_AO.png"));
        helmetMat->SetEmissiveTexture(Texture::Manager::Get("Default_emissive.png"));
        
        helmetObj.EmplaceComponent<StaticMesh>(helmetMesh, helmetMat);
        
        auto objectDistance = 5;
        
        helmetObj.GetTransform().LocalTranslateDelta({-objectDistance,5,0}).LocalScaleDelta(vector3(2.0f));
        
        // the unlit material
        auto star = Instantiate<GameObject>();
        star.SetEntityAttributes(star.GetEntityAttributes() & ~CastsShadowsBit);
        auto starMesh = New<MeshCollectionStatic>(MeshAsset::Manager::Get("sphere"));
        starMaterialInstance = New<StarMatMaterialInstance>(Material::Manager::Get<StarMat>());
        star.EmplaceComponent<StaticMesh>(starMesh, starMaterialInstance);
        star.GetTransform().LocalTranslateDelta({objectDistance,5,0});
        
        // render texture
        auto renderTexture = New<RenderTexture>(640,480);
        
        auto renderTextureCam = Instantiate<GameObject>();
        renderTextureCam.GetTransform().SetLocalPosition({-5,2,10});
        renderTextureCam.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("cube"),New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>()));
        auto& rtcam = renderTextureCam.EmplaceComponent<CameraComponent>();
        rtcam.SetActive(true);
        rtcam.target = renderTexture;

        auto quadEntity = Instantiate<GameObject>();
        auto renderTextureMatInst = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        renderTextureMatInst->SetAlbedoTexture(renderTexture->GetTexture());
        quadEntity.EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("quad"),renderTextureMatInst);
        quadEntity.GetTransform().SetWorldPosition({10,10,0}).SetWorldRotation(vector3{deg_to_rad(90),0,0}).SetLocalScale(5);
#endif
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
        GetApp()->GetMainWindow()->SetRelativeMouseMode(relativeMouseMode);
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
        GetApp()->GetMainWindow()->SetRelativeMouseMode(relativeMouseMode);

        im->BindAction(InputNames::PlayParticle, GetInput(this), &Level::PlayParticle, ActionState::Pressed, CID::ANY);

        GetApp()->inputManager = im;
    }

    void PlayParticle() {
        smokeParticle->Reset();
    }

    void PreTick(float scale) final {
        fsScale = scale;
#if ENABLE_OPAQUES
        starMaterialInstance->pushConstantData.applicationTime = GetApp()->GetCurrentTime();
#endif
    }

    void PostTick(float tickrateScale) final {
        if (glm::length(velvec) > 0.01){
            camRoot.GetTransform().LocalTranslateDelta(velvec);
        }
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
