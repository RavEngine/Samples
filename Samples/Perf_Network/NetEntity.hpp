#pragma once
#include <RavEngine/GameObject.hpp>
#include "NetTransform.hpp"

struct MoveEntities : public RavEngine::AutoCTTI {
	void operator()(PathData& pathdata, RavEngine::NetworkIdentity& netid, RavEngine::Transform& transform) const;
};

struct NetEntity : public RavEngine::GameObject {
#if !RVE_SERVER
	static Ref<RavEngine::PBRMaterialInstance> matinst;
#endif

	void Create();

	// invoked when spawned over the network
	// called *in addition to* not *instead of* Create()
	void ClientCreate() {
		EmplaceComponent<PathData>();
	}
};
