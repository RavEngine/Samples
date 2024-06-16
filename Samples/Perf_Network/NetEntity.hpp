#pragma once
#include <RavEngine/GameObject.hpp>
#include "NetTransform.hpp"

struct MoveEntities : public RavEngine::AutoCTTI {
	void operator()(PathData& pathdata, RavEngine::NetworkIdentity& netid, RavEngine::Transform& transform) const;
};

struct NetEntity : public RavEngine::GameObject {

	static Ref<RavEngine::PBRMaterialInstance> matinst;

	void Create();

	// invoked when spawned over the network
	// called *in addition to* not *instead of* Create()
	void ClientCreate() {
		EmplaceComponent<PathData>();
	}
};
