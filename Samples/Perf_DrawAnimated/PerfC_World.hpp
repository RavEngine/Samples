#pragma once
#include <RavEngine/World.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/GUI.hpp>
#include <RavEngine/App.hpp>
#include <array>
#include "Systems.hpp"

namespace RavEngine {
	struct MeshCollectionStatic;
}

class PerfC_World : public RavEngine::World{
public:
	PerfC_World();
	
	RavEngine::GameObject lightEntity;
	
	static constexpr size_t num_meshes = 4;
	static RavEngine::Array<Ref<RavEngine::MeshCollectionStatic>,num_meshes> meshes;
	
	static constexpr size_t num_textures = 80;
	static RavEngine::Array<Ref<RavEngine::Texture>, num_textures> textures;
	
#ifdef _DEBUG
	static constexpr size_t num_objects = 5000;	//reduced for demo because debug builds are slower
#else
	static constexpr size_t num_objects = 40000;
#endif
	
	static bool TexturesEnabled;
	static bool paused;
    
	bool fullbright = false;
	
	/**
	 Pause or unpause the spinning animations
	 */
	void TogglePause(){
		paused = !paused;
	}
	
	/**
	 Enable or disable texture display
	 */
	void ToggleTextures();
	
	/**
	 Enable or disable fullbright lighting
	 */
	void ToggleFullbright();
    
protected:

	Rml::Element* fpslabel = nullptr;
	RavEngine::ComponentHandle<RavEngine::GUIComponent> hud;
	RavEngine::Array<Ref<RavEngine::PBRMaterialInstance>, PerfC_World::num_textures> materialInstances;
    
	void PostTick(float) override;
};

struct SpinSystem : public RavEngine::AutoCTTI {
    
    inline void operator()(const SpinComponent& c, RavEngine::Transform& tr) const{
        //get the entity and spin it based on the component data
        if (!PerfC_World::paused){
            auto fpsScale = RavEngine::GetApp()->GetCurrentFPSScale();
            tr.LocalRotateDelta((decimalType)fpsScale * c.spinamt);
        }
    }
};

