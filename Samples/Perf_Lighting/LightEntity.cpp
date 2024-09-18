#include "LightEntity.hpp"
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/MeshCollection.hpp>

void LightEntity::Create(Ref<RavEngine::MeshCollectionStatic> mesh)
{
	GameObject::Create();
	auto mat = RavEngine::New<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
	EmplaceComponent<RavEngine::StaticMesh>(mesh,mat);
	auto& cc = EmplaceComponent<CirculateComponent>();
	auto& light = EmplaceComponent<RavEngine::PointLight>();
	light.SetIntensity(cc.radius * 2);
	light.SetColorRGBA({ RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),RavEngine::Random::get(0.f,1.f),1 });
	mat->SetAlbedoColor(light.GetColorRGBA());
	GetTransform().SetLocalScale(0.02);
}
