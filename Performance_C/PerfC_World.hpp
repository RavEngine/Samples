#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <array>

class PerfC_World : public RavEngine::World{
public:
	PerfC_World();
	
	Ref<RavEngine::Entity> lightEntity;
	
	static constexpr size_t num_meshes = 4;
	static std::array<Ref<RavEngine::MeshAsset>,num_meshes> meshes;
	
	void posttick(float) override;
};
