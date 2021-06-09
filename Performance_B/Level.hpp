#include <RavEngine/World.hpp>

struct PerfB_World : public RavEngine::World {
	void OnActivate() override;	//invoked automatically when world is made active
	
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
};
