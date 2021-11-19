#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

struct FlagMat : public RavEngine::PBRMaterial{
    FlagMat() : PBRMaterial("flag"){}
};

struct FlagMatInst : public RavEngine::PBRMaterialInstance{
    FlagMatInst(Ref<FlagMat> f) : PBRMaterialInstance(f){}
};


struct Flagpole : public RavEngine::GameObject{
    void Create();
    struct entry{
        std::string name;
        Ref<RavEngine::PBRMaterialInstance> matInst;
    };
    RavEngine::Vector<entry> flags;
    
    void SwitchToFlag(uint16_t idx);
};
