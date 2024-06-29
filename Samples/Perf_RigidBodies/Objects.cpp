#include "Objects.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;

void Ground::Create()
{
	GameObject::Create();
	auto mat = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	MeshAssetOptions opt;
	opt.keepInSystemRAM = true;
	auto mesh = MeshAsset::Manager::Get("ground.obj", opt);	//need to retain the mesh data in system memory 
	EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(mesh), mat);
	EmplaceComponent<RotationComponent>();
	auto& rs = EmplaceComponent<RigidBodyStaticComponent>();
	rs.EmplaceCollider<MeshCollider>(mesh, New<PhysicsMaterial>(0.3, 0.3, 0.1));

	// system memory copy is no longer needed
	//mesh->DeallocSystemCopy();
}

void RigidBody::Create(Ref<PBRMaterialInstance> mat, Ref<MeshCollectionStatic> mesh, Ref<PhysicsMaterial> physmat, BodyType type)
{
	GameObject::Create();
	EmplaceComponent<StaticMesh>(mesh, mat);
	auto& rd = EmplaceComponent<RigidBodyDynamicComponent>();

	switch (type) {
	case BodyType::Sphere:
		rd.EmplaceCollider<SphereCollider>(1.f, physmat);
		break;
	case BodyType::Cube:
		rd.EmplaceCollider<BoxCollider>(vector3(1, 1, 1), physmat);
		break;
	}
}
