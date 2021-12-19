#pragma once
#include <RavEngine/GameObject.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/Debug.hpp>
#include "NetTransform.hpp"

struct MoveEntities : public RavEngine::AutoCTTI {
	inline void operator()(float fpsScale, PathData& pathdata, RavEngine::NetworkIdentity& netid, RavEngine::Transform& transform) const{

		// use the sine of global time
		if (netid.IsOwner()) {

			auto t = RavEngine::GetApp()->GetCurrentTime();

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
};


struct NetEntity : public RavEngine::GameObject {

	static Ref<RavEngine::PBRMaterialInstance> matinst;

	inline void Create() {
        GameObject::Create();
		auto& rpc = EmplaceComponent<RavEngine::RPCComponent>();
		EmplaceComponent<NetTransform>();
        RavEngine::ComponentHandle<NetTransform> nettransform(this);
        
        auto fn = [nettransform](auto& a, auto b) mutable{
            nettransform->UpdateTransform(a,b);
        };
        rpc.RegisterServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), fn);
		rpc.RegisterClientRPC(RavEngine::to_underlying(RPCs::UpdateTransform), fn);

		if (!matinst) {
			matinst = std::make_shared<RavEngine::PBRMaterialInstance>(RavEngine::Material::Manager::Get<RavEngine::PBRMaterial>());
		}
        RavEngine::MeshAssetOptions opt;
        opt.scale = 0.1;
		EmplaceComponent<RavEngine::StaticMesh>(RavEngine::MeshAsset::Manager::Get("cube.obj",opt), matinst);
		EmplaceComponent<InterpolationTransform>();
	}

	// invoked when spawned over the network
	// called *in addition to* not *instead of* Create()
	inline void ClientCreate() {
		EmplaceComponent<PathData>();
	}
};
