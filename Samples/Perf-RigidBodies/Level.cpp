#include "Level.hpp"
#include "Objects.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/PhysicsLinkSystem.hpp>
#include <FPSSystem.hpp>

using namespace std;
using namespace RavEngine;

static System::list_type runBefore = {CTTI<PhysicsLinkSystemRead>(),CTTI<PhysicsLinkSystemWrite>()};

static inline vector3 GenSpawnpoint(){
	constexpr auto dist = 30;
	return vector3(Random::get(-dist,dist),10,Random::get(-dist,dist));
}

struct RotationSystem : public RavEngine::AutoCTTI{
	
	inline void Tick(float fpsScale, Ref<RotationComponent> rot, Ref<Transform> tr){
		auto time = App::GetCurrentTime();
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
	Ref<Texture> texture;
	
	SpawnerSystem(decltype(ownWorld) world) :
		mat(std::make_shared<PBRMaterialInstance>(Material::Manager::GetMaterial<PBRMaterial>())),
		physmat(std::make_shared<PhysicsMaterial>(0.3, 0.3, 0.1)),
		texture(std::make_shared<Texture>("checkerboard.png")),
		ownWorld(world)
	{
		mat->SetAlbedoTexture(texture);
		mesh = RavEngine::MeshAsset::Manager::GetMesh("sphere.obj",1.0,true);
	}
	
    static constexpr auto total = 5000;
	int count = total;
	
	inline void Tick(float fpsScale, Ref<SpawnerMarker>){
		if (count > 0){
			// spawn rigid bodies
			auto rigid = std::make_shared<RigidBody>(mat,mesh, physmat, RigidBody::BodyType::Sphere);
			
			rigid->GetTransform()->LocalTranslateDelta(GenSpawnpoint());
			rigid->GetTransform()->SetLocalScale(vector3(0.5,0.5,0.5));
            auto own = ownWorld.lock();
            own->Spawn(rigid);
			
			count--;
            
            auto lastTPS = App::CurrentTPS();
            auto lastFPS = App::Renderer->GetCurrentFPS();
            auto guic = own->GetComponent<GUIComponent>().value();
            if (lastTPS > 30 && lastFPS > 30){
                guic->EnqueueUIUpdate([=]{
                    guic->GetDocument("ui.rml")->GetElementById("readout")->SetInnerRML(StrFormat("{}/{} balls", total - count,total));
                });
            }
            else{
                auto spawned = total - count;
                guic->EnqueueUIUpdate([=]{
                    guic->GetDocument("ui.rml")->GetElementById("readout")->SetInnerRML(StrFormat("{}/{} balls (Detected dip in performance, stopping)", spawned,total));
                });
                count = 0;
            }
		}
	}
};

void Level::OnActivate(){
	
	// create camera and lights
	auto camEntity = make_shared<Entity>();
	auto camera = camEntity->EmplaceComponent<CameraComponent>();
	camera->SetActive(true);
	camera->farClip = 1000;
	camEntity->GetTransform()->LocalTranslateDelta(vector3(0,10*5,20*5));
	camEntity->GetTransform()->LocalRotateDelta(vector3(glm::radians(-30.0f),0,0));
    auto gui = camEntity->EmplaceComponent<GUIComponent>();
    gui->AddDocument("ui.rml");
	Spawn(camEntity);
	
	auto lightEntity = make_shared<Entity>();
	auto ambientLight = lightEntity->EmplaceComponent<AmbientLight>();
	auto dirLight = lightEntity->EmplaceComponent<DirectionalLight>();
	lightEntity->EmplaceComponent<SpawnerMarker>();
	dirLight->Intensity = 1.0;
	ambientLight->Intensity = 0.2;
	lightEntity->GetTransform()->SetLocalRotation(vector3(0,glm::radians(45.0),glm::radians(45.0)));
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
    systemManager.EmplaceTimedSystem<FPSSystem>(std::chrono::seconds(1),"ui.rml","metrics");

}
