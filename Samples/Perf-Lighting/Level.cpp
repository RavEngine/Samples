#include "Level.hpp"
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/QueryIterator.hpp>
#include "LightEntity.hpp"

using namespace RavEngine;
using namespace std;

STATIC(LightEntity::lightmesh);

struct SpinComponent : public RavEngine::Component, public Queryable<SpinComponent> {
	float speed = Random::get(0.3,1.5);
};

struct SpinSystem : public RavEngine::AutoCTTI {
	inline constexpr auto QueryTypes() const {
		return QueryIteratorAND<SpinComponent,Transform>();
	}

	inline void Tick(float fpsScale, AccessRead<SpinComponent> s, AccessReadWrite<Transform> t) const {
		t.get()->LocalRotateDelta(vector3(0,glm::radians(fpsScale * s.get()->speed),0));
	}
};

struct StaticMeshEntity : public Entity {
	StaticMeshEntity(Ref<MeshAsset> mesh, Ref<PBRMaterialInstance> mat) {
		EmplaceComponent<StaticMesh>(mesh, mat);
		EmplaceComponent<SpinComponent>();
		constexpr float dist = 1.0;
		transform()->LocalTranslateDelta(vector3(Random::get(-dist,dist), Random::get(-dist, dist), Random::get(-dist, dist)));
	}
};

void Level::OnActivate() {

	// load camera and lights
	auto camera = make_shared<Entity>();
	camera->EmplaceComponent<CameraComponent>()->setActive(true);
	camera->transform()->LocalTranslateDelta(vector3(0,0.5,2));

	auto lights = make_shared<Entity>();
	lights->EmplaceComponent<AmbientLight>()->Intensity = 0.1;
	lights->transform()->LocalRotateDelta(vector3(0,glm::radians(-30.f),glm::radians(45.f)));
	
	Spawn(camera);
	Spawn(lights);

	// load the ground plane
	auto ground = make_shared<Entity>();
	auto mesh = make_shared<MeshAsset>("quad.obj",1.2);
	auto mat = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	mat->SetAlbedoColor({0.2,0.2,0.2,1.0});
	ground->EmplaceComponent<StaticMesh>(mesh,mat);
	Spawn(ground);

	// load the stanford dragon
	auto hmesh = make_shared<MeshAsset>("dragon_vrip.ply", 2);
	auto hmat = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	
	for (int i = 0; i < 50; i++) {
		Spawn(make_shared<StaticMeshEntity>(hmesh,hmat));
	}

	// load Systems
	systemManager.EmplaceSystem<SpinSystem>();
	systemManager.EmplaceSystem<CirculateSystem>();

	// load lights
	for (int i = 0; i < 5; i++) {
		Spawn(make_shared<LightEntity>());
	}

}