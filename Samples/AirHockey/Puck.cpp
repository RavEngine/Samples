#include "Puck.hpp"
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Material.hpp>
#include <RavEngine/PhysicsCollider.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/Light.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/AudioSource.hpp>
#include <RavEngine/RenderEngine.hpp>
#include <RavEngine/PhysicsSolver.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;

void Puck::Create()
{
    GameObject::Create();
    MeshAssetOptions opt;
    if (material == nullptr) {
        material = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
        material->SetAlbedoColor({ 0.2,0.2,0.2,1 });
    }
    auto& puckmesh = EmplaceComponent<StaticMesh>(New<MeshCollectionStatic>(MeshAsset::Manager::Get("HockeyPuck", opt)), material);

    auto& dyn = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);
    dyn.EmplaceCollider<SphereCollider>(0.3f, New<PhysicsMaterial>(0.f, 0.f, 1.f), vector3(0.f, 0.3f, 0.f));

    //prevent puck from falling over
    dyn.SetAxisLock(RigidBodyDynamicComponent::AxisLock::Angular_X | RigidBodyDynamicComponent::AxisLock::Angular_Z);
    dyn.SetMass(1.0);

    auto lightEntity = GetWorld()->Instantiate<GameObject>();

    auto& light = lightEntity.EmplaceComponent<PointLight>();
    light.SetColorRGBA({ 0,0,1,1 });
    light.SetIntensity(2);

    GetTransform().AddChild(ComponentHandle<Transform>(lightEntity));

    lightEntity.GetTransform().LocalTranslateDelta(vector3(0, 1, 0));

    EmplaceComponent<PuckComponent>();

    auto& scr = EmplaceComponent<PuckScript>();

    auto callbackptr = New<PhysicsCallback>();
    auto me = *this;
    callbackptr->OnColliderEnter = [me](PhysicsBodyComponent& other, const ContactPairPoint* contactPoints, size_t numContactPoints) {
        me.GetComponent<PuckScript>().OnColliderEnter(other, contactPoints, numContactPoints);
        };

    dyn.AddReceiver(callbackptr);
}

PuckScript::PuckScript(entity_t owner) : ScriptComponent(owner), sounds{
        New<AudioAsset>("hockeyhit1.wav"),
        New<AudioAsset>("hockeyhit2.wav"),
        New<AudioAsset>("hockeyhit3.wav"),
        New<AudioAsset>("hockeyhit4.wav")
    }
{
}

void PuckScript::OnColliderEnter(PhysicsBodyComponent&, const ContactPairPoint* contactPoints, size_t numContactPoints)
{
    GetOwner().GetWorld()->PlaySound(InstantaneousAudioSource(sounds[std::rand() % 4], GetTransform().GetWorldPosition(), 3));
}
