#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <vector>

struct FlagMat : public RavEngine::PBRMaterial{
    FlagMat() : PBRMaterial("flag"){}
};

struct FlagMatInst : public RavEngine::PBRMaterialInstance{
    FlagMatInst(Ref<FlagMat> f) : PBRMaterialInstance(f){}
};


struct Flagpole : public RavEngine::Entity{
    Flagpole();
    struct entry{
        std::string name;
        Ref<RavEngine::PBRMaterialInstance> matInst;
    };
    std::vector<entry> flags;
    
    void SwitchToFlag(uint16_t idx);
};
