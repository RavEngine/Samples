#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Utilities.hpp>
#include "CustomMaterials.hpp"

struct BasicEntity : public RavEngine::Entity {
	BasicEntity(Ref<RavEngine::MeshAsset> mesh, Ref<InstanceColorMatInstance> matinst) {
		EmplaceComponent<RavEngine::StaticMesh>(mesh,matinst);
	
		vector3 pos;
		pos.x = RavEngine::Random::get(-30, 30);
		pos.y = RavEngine::Random::get(-30, 30);
		pos.z = RavEngine::Random::get(-30, 30);

		vector3 rot(glm::radians(pos.x), glm::radians(pos.y), glm::radians(pos.z));

		transform()->LocalTranslateDelta(pos);
		transform()->LocalRotateDelta(rot);
	}
};
