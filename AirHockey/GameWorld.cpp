#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>

Ref<DefaultMaterialInstance> Puck::material;
using namespace std;

Tween<decimalType,decimalType> t;

Ref<Entity> cameraBoom = new Entity();

GameWorld::GameWorld()
{
	Ref<Entity> cameraActor = new Entity();
	cameraActor->AddComponent<CameraComponent>(new CameraComponent())->setActive(true);
	cameraBoom->transform()->SetWorldPosition(vector3(0,0,0));
	
	cameraBoom->transform()->AddChild(cameraActor->transform());
	cameraActor->transform()->LocalTranslateDelta(vector3(0,3,3));
	cameraActor->transform()->LocalRotateDelta(vector3(glm::radians(-90.0),0,0));
	
	Spawn(cameraActor);
	Spawn(cameraBoom);
    
	auto debugMat = new DefaultMaterialInstance(Material::Manager::AccessMaterialOfType<DefaultMaterial>());

    //create the table
	auto tablemesh = hockeytable->AddComponent<StaticMesh>(new StaticMesh(new MeshAsset("HockeyTable.obj")));
	tablemesh->SetMaterial(debugMat);
	Spawn(hockeytable);
    
    //create the puck
    puck->transform()->LocalTranslateDelta(vector3(0,2,0));
    Spawn(puck);
	
	t = Tween<decimalType,decimalType>([=](decimalType d, decimalType p) -> bool{
		cameraBoom->transform()->SetLocalRotation(vector3(glm::radians(d),glm::radians(90.0),0));
		cameraActor->transform()->SetLocalPosition(vector3(0,p,p));
	},90,10);
	t.AddKeyframe(3, tweeny::easing::quadraticOut,0,3.5);

}
void GameWorld::posttick(float f)
{
	t.step(f);
}
