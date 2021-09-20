#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

struct Flagpole : public RavEngine::Entity{
    Flagpole();
};

struct FlagMat : public RavEngine::PBRMaterial{
    FlagMat() : PBRMaterial("flag"){}
};

struct FlagMatInst : public RavEngine::PBRMaterialInstance{
    FlagMatInst(Ref<FlagMat> f) : PBRMaterialInstance(f){}
};
