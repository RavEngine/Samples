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
	
	static constexpr size_t num_textures = 80;
	static std::array<Ref<RavEngine::Texture>, num_textures> textures;
	
#ifdef _DEBUG
	static constexpr size_t num_objects = 1000;	//reduced for demo because debug builds are slower
#else
	static constexpr size_t num_objects = 3265;
#endif
	
	static bool TexturesEnabled;
	
	bool fullbright = false;
	
	/**
	 Pause or unpause the spinning animations
	 */
	void TogglePause(){
		spinsys->paused = !spinsys->paused;
	}
	
	/**
	 Enable or disable texture display
	 */
	void ToggleTextures(){
		TexturesEnabled = !TexturesEnabled;
	}
	
	/**
	 Enable or disable fullbright lighting
	 */
	void ToggleFullbright();
	
protected:

	Rml::Element* fpslabel = nullptr;
	Ref<RavEngine::GUIComponent> hud;
	
	Ref<SpinSystem> spinsys;
	
	void posttick(float) override;
};
