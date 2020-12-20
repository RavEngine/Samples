#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/Light.hpp>

Ref<PBRMaterialInstance> Puck::material;
using namespace std;

Tween<decimalType,decimalType> t;

static Ref<Entity> cameraBoom = new Entity();

static Ref<Entity> pointLight;
static Ref<Entity> pointLight2;
static Ref<Entity> directionalLight;

static float currentTime = 0;

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
    puck->transform()->LocalTranslateDelta(vector3(0,2,0));
    Spawn(puck);

	InitPhysics();
	
	//intro animation
	t = Tween<decimalType,decimalType>([=](decimalType d, decimalType p){
		cameraBoom->transform()->SetLocalRotation(vector3(glm::radians(d),glm::radians(90.0),0));
		cameraActor->transform()->SetLocalPosition(vector3(0,p,0));
	},90,15);
	t.AddKeyframe(3, TweenCurves::QuinticInOutCurve,0,7);

	puck->Components().GetComponent<RigidBodyDynamicComponent>()->SetLinearVelocity(vector3(10, 7, 0), true);
	
	pointLight = new Entity();
	pointLight->AddComponent<PointLight>(new PointLight())->Intensity = 1;
	pointLight->Components().GetComponent<PointLight>()->color = ColorRGBA{0,0.5,1,1};
    
    pointLight2 = new Entity();
    pointLight2->AddComponent<PointLight>(new PointLight())->Intensity=1;
    pointLight2->transform()->LocalTranslateDelta(vector3(0,3,-1));
	
	directionalLight = new Entity();
	directionalLight->AddComponent<DirectionalLight>(new DirectionalLight())->Intensity=0.4;
	
	Spawn(pointLight);
    Spawn(pointLight2);
	Spawn(directionalLight);
}
void GameWorld::posttick(float f)
{
	currentTime += f;
	t.step(f);
	pointLight->transform()->SetLocalPosition(vector3(cos(currentTime/50)*3,2,sin(currentTime/50)*5));
	pointLight2->transform()->SetLocalPosition(vector3(sin(currentTime/70)*3,2,cos(currentTime/70)*5));
	
	//directionalLight->transform()->SetWorldRotation(vector3(0,0,glm::radians(currentTime)));
	
	directionalLight->transform()->SetLocalRotation(vector3(glm::radians(cos(currentTime/80)*30),0,glm::radians(sin(currentTime/60)*30)));
}
