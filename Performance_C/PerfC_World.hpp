#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/GUI.hpp>
#include <array>
#include "Systems.hpp"

class PerfC_World : public RavEngine::World{
public:
	PerfC_World();
	
	Ref<RavEngine::Entity> lightEntity;
	
	static constexpr size_t num_meshes = 4;
	static std::array<Ref<RavEngine::MeshAsset>,num_meshes> meshes;
	
	static constexpr size_t num_textures = 1;
	static std::array<Ref<RavEngine::Texture>, num_textures> textures;
	
protected:

	Rml::Element* fpslabel = nullptr;
	
	Ref<SpinSystem> spinsys;
	
	void posttick(float) override;
};
