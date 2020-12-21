#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/Light.hpp>
#include "Paddle.hpp"

Ref<PBRMaterialInstance> Puck::material;
using namespace std;

Tween<decimalType,decimalType> t;

static Ref<Entity> cameraBoom = new Entity();

static Ref<Paddle> p1;

static float currentTime = 0;

Ref<PBRMaterialInstance> Paddle::material;

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
	Spawn(hockeytable);
    
    //create the puck
    puck->transform()->LocalTranslateDelta(vector3(0,3,0));
    Spawn(puck);

	InitPhysics();
	
	//intro animation
	t = Tween<decimalType,decimalType>([=](decimalType d, decimalType p){
		cameraBoom->transform()->SetLocalRotation(vector3(glm::radians(d),glm::radians(90.0),0));
		cameraActor->transform()->SetLocalPosition(vector3(0,p,0));
	},90,15);
	t.AddKeyframe(3, TweenCurves::QuinticInOutCurve,0,7);
	
	Ref<Entity> lightmain = new Entity();
	auto key = lightmain->AddComponent<DirectionalLight>(new DirectionalLight());
	key->Intensity = 0.8;
	key->color = {1,0.6,0.404,1};
	auto fill = lightmain->AddComponent<AmbientLight>(new AmbientLight());
	fill->Intensity=0.4;
	fill->color = {0.7,1,1,1};
	lightmain->transform()->LocalRotateDelta(vector3(glm::radians(45.0),0,glm::radians(-45.0)));

	Spawn(lightmain);
	
	p1 = new Paddle();
	p1->transform()->LocalTranslateDelta(vector3(0,1.4,1));
	Spawn(p1);
}
void GameWorld::posttick(float f)
{
	currentTime += f;
	t.step(f);
	
	p1->Components().GetComponent<CapsuleCollider>()->DebugDraw();
	puck->Components().GetComponent<PhysicsCollider>()->DebugDraw();
	
	p1->transform()->SetLocalPosition(vector3(sin(currentTime/50)*3,1.4,cos(currentTime/40)*2));

}
