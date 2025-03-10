#pragma once
#include <RavEngine/BuiltinMaterials.hpp>
#include <ravengine_shader_defs.h>

struct MatInstUniforms {
	float time = 0;
};

struct InstanceColorMat : public RavEngine::LitMaterial {
	InstanceColorMat() : LitMaterial("instance_colored", { .pushConstantSize = sizeof(MatInstUniforms)}) {}
};

struct InstanceColorMatInstance : public RavEngine::MaterialInstance{
	InstanceColorMatInstance(Ref<InstanceColorMat> m) : MaterialInstance(m) { };
	void SetTime(decltype(MatInstUniforms::time) time) {
		pushConstantData.time = time;
	}
	virtual const RGL::untyped_span GetPushConstantData() const override {
		return pushConstantData;
	}
private:
	MatInstUniforms pushConstantData{};
};
