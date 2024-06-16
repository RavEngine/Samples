#include "Level.hpp"
#include "Objects.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/PhysicsLinkSystem.hpp>
#include <FPSSystem.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/Texture.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace std;
using namespace RavEngine;

static inline vector3 GenSpawnpoint(){
	constexpr auto dist = 30;
	return vector3(Random::get(-dist,dist),10,Random::get(-dist,dist));
}

struct RotationSystem : public RavEngine::AutoCTTI{
	
	inline void operator()(const RotationComponent& rotation, Transform& transform) const{
		auto time = GetApp()->GetCurrentTime();
		decimalType xrot = std::sin(time * rotation.xspeed) * rotation.maxDeg;
		decimalType yrot = std::sin(time * rotation.yspeed) * rotation.maxDeg;
		decimalType zrot = std::sin(time * rotation.zspeed) * rotation.maxDeg;
		
		transform.SetLocalRotation(vector3(deg_to_rad(xrot),deg_to_rad(yrot),deg_to_rad(zrot)));
	}
};

struct RespawnSystem : public RavEngine::AutoCTTI{
	inline void operator()(RigidBodyDynamicComponent& rigid, Transform& transform) const{
		if (transform.GetWorldPosition().y < -20){
			rigid.setDynamicsWorldPose(GenSpawnpoint(), transform.GetWorldRotation());
			rigid.SetLinearVelocity(vector3(0,0,0), false);
		}
	}
};

struct SpawnerMarker : public AutoCTTI{};

struct SpawnerSystem : public RavEngine::AutoCTTI{
	Level* ownWorld;
	Ref<MeshCollectionStatic> mesh;
	Ref<PBRMaterialInstance> mat;
	Ref<PhysicsMaterial> physmat;
	Ref<Texture> texture;
    ComponentHandle<GUIComponent> gh;
	
	SpawnerSystem(decltype(ownWorld) world, decltype(gh) gh_i) :
		mat(RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())),
		physmat(RavEngine::New<PhysicsMaterial>(0.3, 0.3, 0.1)),
		texture(Texture::Manager::Get("checkerboard.png")),
		ownWorld(world),
        gh(gh_i)
	{
		mat->SetAlbedoTexture(texture);
        MeshAssetOptions opt;
        opt.keepInSystemRAM = true;
		mesh = RavEngine::MeshCollectionStaticManager::Get("sphere.obj",opt);
	}
	
    static constexpr auto total = 20000;
	int count = total;
    
    int totalLostTicks = 0;
    static constexpr auto maxLostTicks = 100;
	
	inline void operator()(SpawnerMarker&){
		if (count > 0){
			// spawn rigid bodies
			GetApp()->DispatchMainThread([&](){
                auto rigid = ownWorld->Instantiate<RigidBody>(mat,mesh, physmat, RigidBody::BodyType::Sphere);
				rigid.GetComponent<RigidBodyDynamicComponent>().setDynamicsWorldPose(GenSpawnpoint(),quaternion(0,0,0,1));

                rigid.GetTransform().SetLocalScale(vector3(0.5,0.5,0.5));
            });
            
			count--;
            
            auto lastTPS = GetApp()->CurrentTPS();
            auto& guic = ownWorld->GetComponent<GUIComponent>();
            if (total - count > 30 && ( lastTPS < 20 )){
                totalLostTicks++;
            }
            if(totalLostTicks < maxLostTicks){
                guic.EnqueueUIUpdate([=]{
                    gh->GetDocument("ui.rml")->GetElementById("readout")->SetInnerRML(Format("{}/{} balls (dropped {})", total - count,total,totalLostTicks));
                });
            }
            else{
                auto spawned = total - count;
                guic.EnqueueUIUpdate([=]{
                    gh->GetDocument("ui.rml")->GetElementById("readout")->SetInnerRML(Format("{}/{} balls (sustained &lt; 20fps, stopping)", spawned,total));
                });
                ownWorld->DispatchAsync([](){
                    Debug::Log("Ran dispatched fun");
                }, 3);
                count = 0;
            }
		}
	}
};

Level::Level(){
	
	// create camera and lights
	auto camEntity = Instantiate<GameObject>();
	auto& camera = camEntity.EmplaceComponent<CameraComponent>();
	camera.SetActive(true);
	camera.farClip = 1000;
	camEntity.GetTransform().LocalTranslateDelta(vector3(0,10*5,20*5)).LocalRotateDelta(vector3(deg_to_rad(-30),0,0));
    auto& gui = camEntity.EmplaceComponent<GUIComponent>();
    gui.AddDocument("ui.rml");
	
	auto lightEntity = Instantiate<GameObject>();
	auto& ambientLight = lightEntity.EmplaceComponent<AmbientLight>();
	auto& dirLight = lightEntity.EmplaceComponent<DirectionalLight>();
	lightEntity.EmplaceComponent<SpawnerMarker>();
	dirLight.SetIntensity(4);
	dirLight.SetCastsShadows(true);
    dirLight.SetShadowDistance(160);
	ambientLight.SetIntensity(0.2);
	lightEntity.GetTransform().SetLocalRotation(vector3(0,deg_to_rad(45),deg_to_rad(45)));
	
	// create ground
	auto ground = Instantiate<Ground>();
	
	// initialize physics
	InitPhysics();
	
	// load systems
	EmplaceSystem<RotationSystem>();
    
    CreateDependency<RotationSystem, PhysicsLinkSystemRead>();
    CreateDependency<RotationSystem, PhysicsLinkSystemWrite>();
    
	EmplaceSystem<RespawnSystem>();
    CreateDependency<RespawnSystem, PhysicsLinkSystemRead>();
    CreateDependency<RespawnSystem, PhysicsLinkSystemWrite>();
    
	EmplaceTimedSystem<SpawnerSystem>(std::chrono::milliseconds(50),this,ComponentHandle<GUIComponent>(camEntity));
    EmplaceTimedSystem<FPSSystem>(std::chrono::seconds(1),"ui.rml","metrics");

}
