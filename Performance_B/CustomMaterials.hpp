#pragma once
#include <RavEngine/BuiltinMaterials.hpp>

struct InstanceColorMat : public RavEngine::PBRMaterial {
	InstanceColorMat() : PBRMaterial("instance_colored"){}
};

struct InstanceColorMatInstance : public RavEngine::PBRMaterialInstance{
	InstanceColorMatInstance(Ref<InstanceColorMat> m) : PBRMaterialInstance(m) { };
};
