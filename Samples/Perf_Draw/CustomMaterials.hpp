#pragma once
#include <RavEngine/BuiltinMaterials.hpp>

struct MatInstUniforms {
	float time = 0;
};

struct InstanceColorMat : public RavEngine::Material {
	InstanceColorMat() : Material("instance_colored", RavEngine::MaterialConfig{
			.vertConfig = RavEngine::defaultVertexConfig,
			.colorBlendConfig = RavEngine::defaultColorBlendConfig,
			.bindings = {
				{
					.binding = 2,
					.type = RGL::BindingType::StorageBuffer,
					.stageFlags = RGL::BindingVisibility::Vertex
				}
            },
			.pushConstantSize = sizeof(MatInstUniforms)
		
		}) {}
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
