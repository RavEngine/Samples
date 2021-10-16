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

		GetTransform()->LocalTranslateDelta(pos);
		GetTransform()->LocalRotateDelta(rot);
	}
};

struct InstanceEntity : public RavEngine::Entity{
    InstanceEntity(Ref<RavEngine::MeshAsset> mesh, Ref<InstanceColorMatInstance> matinst, uint32_t count){
        auto ism = EmplaceComponent<RavEngine::InstancedStaticMesh>(mesh,matinst);
        ism->Reserve(count);
        
        for(uint32_t i = 0; i < count; i++){
            vector3 pos;
            pos.x = RavEngine::Random::get(-30, 30);
            pos.y = RavEngine::Random::get(-30, 30);
            pos.z = RavEngine::Random::get(-30, 30);

            vector3 rot(glm::radians(pos.x), glm::radians(pos.y), glm::radians(pos.z));
            
            auto& inst = ism->AddInstance();
            inst.translate = pos;
            inst.rotate = rot;
            inst.scale = vector3(1,1,1);
        }
    }
};
