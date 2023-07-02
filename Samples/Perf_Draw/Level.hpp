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
	
	void SwitchMesh(meshes nextMesh){
		switch (prevMesh){
			case meshes::cube:
				cube->Exchange(currentMesh,false);
				break;
			case meshes::cone:
				cone->Exchange(currentMesh,false);
				break;
			case meshes::cylinder:
				cylinder->Exchange(currentMesh,false);
				break;
			case meshes::sphere:
				sphere->Exchange(currentMesh,false);
				break;
		}
		prevMesh = nextMesh;
		
		switch(nextMesh){
			case meshes::cube:
				currentMesh->Exchange(cube,false);
				break;
			case meshes::cone:
				currentMesh->Exchange(cone,false);
				break;
			case meshes::cylinder:
				currentMesh->Exchange(cylinder,false);
				break;
			case meshes::sphere:
				currentMesh->Exchange(sphere,false);
				break;
		}
	}
private:
	Ref<RavEngine::MeshAsset> currentMesh, cube, cone, cylinder, sphere;
	Ref<struct InstanceColorMatInstance> matinst;
	void PreTick(float fpsscale) override;
};
