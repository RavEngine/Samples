#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>

Ref<DefaultMaterialInstance> Puck::material;
using namespace std;

Tween t;

GameWorld::GameWorld()
{
	Ref<Entity> cameraActor = new Entity();
	cameraActor->AddComponent<CameraComponent>(new CameraComponent())->setActive(true);
	cameraActor->transform()->LocalTranslateDelta(vector3(0,5,10));
	cameraActor->transform()->LocalRotateDelta(vector3(glm::radians(-30.0),0,0));

	Spawn(cameraActor);
    
	auto debugMat = new DefaultMaterialInstance(Material::Manager::AccessMaterialOfType<DefaultMaterial>());

    //create the table
	auto tablemesh = hockeytable->AddComponent<StaticMesh>(new StaticMesh(new MeshAsset("HockeyTable.obj")));
	tablemesh->SetMaterial(debugMat);
	Spawn(hockeytable);
    
    //create the puck
    puck->transform()->LocalTranslateDelta(vector3(0,2,0));
    Spawn(puck);
	
	t = Tween([=](decimalType d) -> bool{
		hockeytable->transform()->SetLocalRotation(vector3(0,d*0.01,0));
	});
	t.AddKeyframe(100, 5, tweeny::easing::linear).AddKeyframe(-100, 5, tweeny::easing::quadraticOut);

}
void GameWorld::posttick(float f)
{
	t.step(f);
}
