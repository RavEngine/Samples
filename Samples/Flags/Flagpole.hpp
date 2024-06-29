#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Texture.hpp>
#include <ravengine_shader_defs.h>

struct FlagMatUniforms {
    float time = 0;
};

struct FlagMat : public RavEngine::LitMaterial {
    FlagMat(std::string_view secondShader = "flag") : LitMaterial("flag", secondShader, {
            .bindings = {
                {
                    .binding = 0,
                    .type = RGL::BindingType::Sampler,
                    .stageFlags = RGL::BindingVisibility::Fragment,
                },
                 {
                    .binding = 1,
                    .type = RGL::BindingType::SampledImage,
                    .stageFlags = RGL::BindingVisibility::Fragment,
                },
            },
        .pushConstantSize = sizeof(FlagMatUniforms)
        }, {        
        .cullMode = RGL::CullMode::None
        }) {}
};

struct FlagMatInst : public RavEngine::MaterialInstance{
    FlagMatInst(Ref<FlagMat> f) : MaterialInstance(f){
        SetAlbedoTexture(RavEngine::Texture::Manager::defaultTexture);
    }
    void SetTime(float time) {
        pushConstantData.time = time;
    }
    void SetAlbedoTexture(Ref<RavEngine::Texture> texture) {
        textureBindings[1] = texture;
    }

    virtual const RGL::untyped_span GetPushConstantData() const override {
        return pushConstantData;
    }
private:
    FlagMatUniforms pushConstantData;
};


struct Flagpole : public RavEngine::GameObject{
    void Create();
    struct entry{
        std::string name;
        Ref<FlagMatInst> matInst;
    };
    RavEngine::Vector<entry> flags;
    
    void SwitchToFlag(uint16_t idx);
    Ref<RavEngine::MaterialInstance> GetCurrentMaterial();
};
