#include "Paddle.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/PhysicsSolver.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;

void Paddle::Create(const ColorRGBA& color)
{
	GameObject::Create();
	MeshAssetOptions opt;

	Ref<PBRMaterialInstance> material = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	material->SetAlbedoColor(color);
	auto& mesh = EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(MeshAsset::Manager::Get("HockeyPaddle", opt)), material);

	//PhysX doesn't have a cylinder primitive, so we use a sphere offset upwards and lock the axes
	auto& dyn = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);

	dyn.EmplaceCollider<SphereCollider>(0.5f, New<PhysicsMaterial>(0.3f, 0.3f, 0.1f), vector3(0, 0.4, 0));

	dyn.SetMass(2);
	dyn.SetAxisLock(
		RigidBodyDynamicComponent::AxisLock::Angular_X |
		RigidBodyDynamicComponent::AxisLock::Angular_Z
		//| RigidBodyDynamicComponent::AxisLock::Linear_Y
	);


	auto& light = EmplaceComponent<PointLight>();
	light.SetColorRGBA(color);
	light.SetIntensity(2);
}
