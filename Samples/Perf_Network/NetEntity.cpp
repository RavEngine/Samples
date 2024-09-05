#include "NetEntity.hpp"
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Debug.hpp>
#include <RavEngine/MeshCollection.hpp>

using namespace RavEngine;

void NetEntity::Create()
{
	GameObject::Create();
	auto& rpc = EmplaceComponent<RPCComponent>();
	EmplaceComponent<NetTransform>();
	ComponentHandle<NetTransform> nettransform(this);
	auto world = GetWorld();
	auto fn = [nettransform, world](auto unpacker, auto b) mutable {
		nettransform->UpdateTransform(unpacker, b);
		};
	rpc.RegisterServerRPC(to_underlying(RPCs::UpdateTransform), fn);
	rpc.RegisterClientRPC(to_underlying(RPCs::UpdateTransform), fn, RPCComponent::Directionality::Bidirectional);

	if (!matinst) {
		matinst = New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
	}
	MeshAssetOptions opt;
	opt.scale = 0.1;
	EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("cube", opt), matinst);
	EmplaceComponent<InterpolationTransform>();
}

void MoveEntities::operator()(PathData& pathdata, NetworkIdentity& netid, Transform& transform) const
{
	// use the sine of global time
	if (netid.IsOwner()) {

		auto t = GetApp()->GetCurrentTime();

		auto pos = vector3(
			std::sin(t * pathdata.xtiming + pathdata.offset) * pathdata.scale,
			std::sin(t * pathdata.ytiming + pathdata.offset) * pathdata.scale,
			std::sin(t * pathdata.ztiming + pathdata.offset) * pathdata.scale
		);
		transform.SetWorldPosition(pos);
		auto rot = quaternion(pos);
		transform.SetLocalRotation(rot);
	}
}
