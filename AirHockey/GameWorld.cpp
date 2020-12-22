#include "GameWorld.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/InputManager.hpp>

Ref<PBRMaterialInstance> Puck::material;
using namespace std;

Tween<decimalType,decimalType> t;

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
	key->Intensity = 1;
	key->color = {1,0.6,0.404,1};
	auto fill = lightmain->AddComponent<AmbientLight>(new AmbientLight());
	fill->Intensity=0.4;
	fill->color = {0.7,1,1,1};
	lightmain->transform()->LocalRotateDelta(vector3(glm::radians(45.0),0,glm::radians(-45.0)));

	Spawn(lightmain);
	
	//inputs
	Ref<InputManager> is = App::inputManager;
	is->AddAxisMap("P1MoveUD", SDL_SCANCODE_W,-1);
	is->AddAxisMap("P1MoveUD", SDL_SCANCODE_S);
	is->AddAxisMap("P1MoveLR", SDL_SCANCODE_D,-1);
	is->AddAxisMap("P1MoveLR", SDL_SCANCODE_A);
	
	is->AddAxisMap("P2MoveUD", SDL_SCANCODE_UP,-1);
	is->AddAxisMap("P2MoveUD", SDL_SCANCODE_DOWN);
	is->AddAxisMap("P2MoveLR", SDL_SCANCODE_RIGHT,-1);
	is->AddAxisMap("P2MoveLR", SDL_SCANCODE_LEFT);
	
	p1 = new Paddle();
	p1->Components().GetComponent<StaticMesh>()->GetMaterial()->SetAlbedoColor({1,0,0,1});
	auto p1s = p1->AddComponent<Player>(new Player());
	Spawn(p1);
	
	p2 = new Paddle();
	p2->Components().GetComponent<StaticMesh>()->GetMaterial()->SetAlbedoColor({0,1,0,1});
	auto p2s = p2->AddComponent<Player>(new Player());
	Spawn(p2);
	
	//bind inputs
	is->BindAxis("P1MoveUD", p1s.get(), &Player::MoveUpDown, CID::ANY);
	is->BindAxis("P1MoveLR", p1s.get(), &Player::MoveLeftRight, CID::ANY);
	
	is->BindAxis("P2MoveUD", p2s.get(), &Player::MoveUpDown, CID::ANY);
	is->BindAxis("P2MoveLR", p2s.get(), &Player::MoveLeftRight, CID::ANY);
	
	Reset();
}
void GameWorld::posttick(float f)
{
	t.step(f);
	
	//if the puck's z position > 6 then the right side must have scored
	auto pos = puck->transform()->GetWorldPosition();
	if (pos.z > 6){
		cout << "Right won!" << endl;
		p1score++;
		Reset();
	}
	else if (pos.z < -6){
		cout << "Left won!" << endl;
		p2score++;
		Reset();
		
	}
}

void GameWorld::Reset(){
	puck->transform()->SetWorldPosition(vector3(0,2,0));
	p1->transform()->SetWorldPosition(vector3(2,2,3));
	p2->transform()->SetWorldPosition(vector3(-2,2,-3));

	//clear velocities
	auto zerovel = [](Ref<Entity> e){
		e->Components().GetComponent<RigidBodyDynamicComponent>()->SetLinearVelocity(vector3(0,0,0), false);
	};
	
	zerovel(p1);
	zerovel(p2);
	zerovel(puck);
}
