#include "Level.hpp"
#include "Objects.hpp"
#include <RavEngine/AccessType.hpp>
#include <RavEngine/App.hpp>
#include <RavEngine/QueryIterator.hpp>

using namespace std;
using namespace RavEngine;

struct RotationSystem : public RavEngine::AutoCTTI{
	
	inline void Tick(float fpsScale, AccessRead<RotationComponent> rot, AccessReadWrite<Transform> tr){
		auto time = App::currentTime();
		auto rotation = rot.get();
		auto transform = tr.get();
		decimalType xrot = std::sin(time * rotation->xspeed) * rotation->maxDeg;
		decimalType yrot = std::sin(time * rotation->yspeed) * rotation->maxDeg;
		decimalType zrot = std::sin(time * rotation->zspeed) * rotation->maxDeg;
		
		transform->SetLocalRotation(vector3(glm::radians(xrot),glm::radians(yrot),glm::radians(zrot)));
	}
	
	inline constexpr QueryIteratorAND<RotationComponent,Transform> QueryTypes() const{
		return QueryIteratorAND<RotationComponent,Transform>();
	}
};

void Level::OnActivate(){
	
	// create camera and lights
	auto camEntity = make_shared<Entity>();
	auto camera = camEntity->EmplaceComponent<CameraComponent>();
	camera->setActive(true);
	camEntity->transform()->LocalTranslateDelta(vector3(0,1,30));
	Spawn(camEntity);
	
	auto lightEntity = make_shared<Entity>();
	auto ambientLight = lightEntity->EmplaceComponent<AmbientLight>();
	auto dirLight = lightEntity->EmplaceComponent<DirectionalLight>();
	dirLight->Intensity = 1.0;
	ambientLight->Intensity = 0.2;
	lightEntity->transform()->SetLocalRotation(vector3(0,glm::radians(45.0),glm::radians(45.0)));
	Spawn(lightEntity);
	
	// create ground
	auto ground = std::make_shared<Ground>();
	Spawn(ground);
	
	// load systems
	systemManager.EmplaceSystem<RotationSystem>();
}
