#pragma once
#include <RavEngine/Entity.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Utilities.hpp>
#include "CustomMaterials.hpp"

struct InstanceEntity : public RavEngine::Entity{
    InstanceEntity(Ref<RavEngine::MeshAsset> mesh, Ref<InstanceColorMatInstance> matinst, uint32_t count, int32_t range = 30){
        auto ism = EmplaceComponent<RavEngine::InstancedStaticMesh>(mesh,matinst);
        ism->Reserve(count);
        
        for(uint32_t i = 0; i < count; i++){
            vector3 pos;
            pos.x = RavEngine::Random::get(-range, range);
            pos.y = RavEngine::Random::get(-range, range);
            pos.z = RavEngine::Random::get(-range, range);

            vector3 rot(glm::radians(pos.x), glm::radians(pos.y), glm::radians(pos.z));
            
            auto& inst = ism->AddInstance();
            inst.translate = pos;
            inst.rotate = rot;
            inst.scale = vector3(1,1,1);
        }
    }
};
