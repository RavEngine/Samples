#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>

Ref<DefaultMaterialInstance> Puck::material;

GameWorld::GameWorld()
{
	Ref<Entity> cameraActor = new Entity();
	cameraActor->AddComponent<CameraComponent>(new CameraComponent())->setActive(true);
	cameraActor->transform()->LocalTranslateDelta(vector3(0,5,10));
	cameraActor->transform()->LocalRotateDelta(vector3(glm::radians(-30.0),0,0));

	Spawn(cameraActor);
    
    auto debugMat = Ref<DefaultMaterialInstance>(new DefaultMaterialInstance(Material::Manager::GetMaterialByName("cubes")));

    //create the table
	auto tablemesh = hockeytable->AddComponent<StaticMesh>(new StaticMesh(new MeshAsset("HockeyTable.obj")));
	tablemesh->SetMaterial(debugMat);
	Spawn(hockeytable);
    
    //create the puck
    puck->transform()->LocalTranslateDelta(vector3(0,2,0));
    Spawn(puck);

}

void GameWorld::posttick(float f)
{
	hockeytable->transform()->LocalRotateDelta(vector3(0, glm::radians(1.0 * f), 0));
}
