#include "PerfC_World.hpp"
#include <RavEngine/Entity.hpp>
#include "Camera.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include "Systems.hpp"

using namespace RavEngine;
using namespace std;

std::array<Ref<MeshAsset>,PerfC_World::num_meshes> PerfC_World::meshes;

static std::random_device rd; // obtain a random number from hardware
static std::mt19937 gen(rd()); // seed the generator
static std::uniform_int_distribution<> rng(-40, 40);
static std::uniform_int_distribution<> meshrng(0, PerfC_World::num_meshes);
static std::uniform_real_distribution<> spinrng(glm::radians(-2.0), glm::radians(2.0));
static std::uniform_real_distribution<> colorrng(0,1);


struct DemoObject : public RavEngine::Entity{
	DemoObject(){
		Ref<Entity> child = new Entity();
		
		AddComponent<ChildEntityComponent>(new ChildEntityComponent(child));
		AddComponent<SpinComponent>(new SpinComponent(vector3(spinrng(gen)/3,spinrng(gen)/3,spinrng(gen)/3)));
		
		auto mesh = child->AddComponent<StaticMesh>(new StaticMesh(PerfC_World::meshes[meshrng(gen)]));
		Ref<PBRMaterialInstance> inst = new PBRMaterialInstance(Material::Manager::AccessMaterialOfType<PBRMaterial>());
		inst->SetAlbedoColor({(float)colorrng(gen),(float)colorrng(gen),(float)colorrng(gen),1});
		mesh->SetMaterial(inst);
		
		transform()->AddChild(child->transform());
		
		child->transform()->LocalTranslateDelta(vector3(rng(gen),rng(gen),rng(gen)));
		
		child->AddComponent<SpinComponent>(new SpinComponent(vector3(spinrng(gen),spinrng(gen),spinrng(gen))));
	}
};

PerfC_World::PerfC_World(){
	meshes[0] = new MeshAsset("cube.obj");
	meshes[1] = new MeshAsset("sphere.obj");
	meshes[2] = new MeshAsset("cone.obj");
	meshes[3] = new MeshAsset("cylinder.obj");
	
	Ref<Camera> cam = new Camera();
	cam->transform()->LocalTranslateDelta(vector3(0,0,50));
	
	Spawn(cam);
	
	lightEntity = new Entity();
	auto al = lightEntity->AddComponent<AmbientLight>(new AmbientLight());
	al->Intensity = 0.3;
	
	auto dl = lightEntity->AddComponent<DirectionalLight>(new DirectionalLight());
	dl->color = {0.7,1,1,1};
	
	
	for(int i = 0; i < 20; i++){
		Spawn(new DemoObject());
	}
	
	Spawn(lightEntity);
	
	RegisterSystem<SpinSystem>(new SpinSystem());
}

void PerfC_World::posttick(float scale){
	
}
