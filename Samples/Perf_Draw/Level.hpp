#include <RavEngine/World.hpp>
#include <RavEngine/MeshAsset.hpp>

struct PerfB_World : public RavEngine::World {
	PerfB_World();	
	
	enum class meshes {
		cube,
		cone,
		cylinder,
		sphere
	} prevMesh = meshes::cube;
	
	void SwitchMesh(meshes nextMesh);
private:
	Ref<RavEngine::MeshAsset> cube, cone, cylinder, sphere;
	Ref<RavEngine::MeshCollectionStatic> meshCollection;
	Ref<struct InstanceColorMatInstance> matinst;
	void PreTick(float fpsscale) override;
};
