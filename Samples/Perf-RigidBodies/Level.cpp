#include "Level.hpp"
#include "Objects.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/PhysicsLinkSystem.hpp>

using namespace std;
using namespace RavEngine;

static System::list_type runBefore = {CTTI<PhysicsLinkSystemRead>(),CTTI<PhysicsLinkSystemWrite>()};

static inline vector3 GenSpawnpoint(){
	constexpr auto dist = 30;
	return vector3(Random::get(-dist,dist),10,Random::get(-dist,dist));
}

struct RotationSystem : public RavEngine::AutoCTTI{
	
	inline void Tick(float fpsScale, Ref<RotationComponent> rot, Ref<Transform> tr){
		auto time = App::currentTime();
		auto rotation = rot.get();
		auto transform = tr.get();
		decimalType xrot = std::sin(time * rotation->xspeed) * rotation->maxDeg;
		decimalType yrot = std::sin(time * rotation->yspeed) * rotation->maxDeg;
		decimalType zrot = std::sin(time * rotation->zspeed) * rotation->maxDeg;
		
		transform->SetLocalRotation(vector3(glm::radians(xrot),glm::radians(yrot),glm::radians(zrot)));
	}
	
	inline const System::list_type& MustRunBefore() const{
		return runBefore;
	}
};

struct RespawnSystem : public RavEngine::AutoCTTI{
	inline void Tick(float fpsScale, Ref<RigidBodyDynamicComponent> rigid, Ref<Transform> transform){
		if (transform->GetWorldPosition().y < -20){
			transform->SetWorldPosition(GenSpawnpoint());
				rigid->SetLinearVelocity(vector3(0,0,0), false);
		}
	}
	
	inline const System::list_type& MustRunBefore() const{
		return runBefore;
	}
};

struct SpawnerMarker : public RavEngine::Component, public RavEngine::Queryable<SpawnerMarker>{};

struct SpawnerSystem : public RavEngine::AutoCTTI{
	WeakRef<Level> ownWorld;
	Ref<MeshAsset> mesh;
	Ref<PBRMaterialInstance> mat;
	Ref<PhysicsMaterial> physmat;
	
	SpawnerSystem(decltype(ownWorld) world) :
		mat( std::make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>())),
		physmat(std::make_shared<PhysicsMaterial>(0.3,0.3,0.1)),
		ownWorld(world)
	{
			
		mesh = std::make_shared<MeshAsset>("sphere.obj",1.0,true);
	}
	
	int count = 500;
	
	inline void Tick(float fpsScale, Ref<SpawnerMarker>){
		if (count > 0){
			// spawn rigid bodies
			auto rigid = std::make_shared<RigidBody>(mat,mesh, physmat, RigidBody::BodyType::Sphere);
			
			rigid->transform()->LocalTranslateDelta(GenSpawnpoint());
			rigid->transform()->SetLocalScale(vector3(0.5,0.5,0.5));
			ownWorld.lock()->Spawn(rigid);
			
			count--;
		}
	}
};

void Level::OnActivate(){
	
	// create camera and lights
	auto camEntity = make_shared<Entity>();
	auto camera = camEntity->EmplaceComponent<CameraComponent>();
	camera->setActive(true);
	camera->farClip = 1000;
	camEntity->transform()->LocalTranslateDelta(vector3(0,10*5,20*5));
	camEntity->transform()->LocalRotateDelta(vector3(glm::radians(-30.0f),0,0));
	Spawn(camEntity);
	
	auto lightEntity = make_shared<Entity>();
	auto ambientLight = lightEntity->EmplaceComponent<AmbientLight>();
	auto dirLight = lightEntity->EmplaceComponent<DirectionalLight>();
	lightEntity->EmplaceComponent<SpawnerMarker>();
	dirLight->Intensity = 1.0;
	ambientLight->Intensity = 0.2;
	lightEntity->transform()->SetLocalRotation(vector3(0,glm::radians(45.0),glm::radians(45.0)));
	Spawn(lightEntity);
	
	// create ground
	auto ground = std::make_shared<Ground>();
	Spawn(ground);
	
	// initialize physics
	InitPhysics();
	
	// load systems
	systemManager.EmplaceSystem<RotationSystem>();
	systemManager.EmplaceSystem<RespawnSystem>();
	systemManager.EmplaceTimedSystem<SpawnerSystem>(std::chrono::milliseconds(100),static_pointer_cast<Level>(shared_from_this()) );
}
