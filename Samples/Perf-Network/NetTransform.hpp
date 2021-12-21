#pragma once
#include <RavEngine/Queryable.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Transform.hpp>
#include <RavEngine/ComponentWithOwner.hpp>

enum class RPCs {
	UpdateTransform,
};

struct InterpolationTransform : public RavEngine::AutoCTTI {
	RavEngine::SpinLock mtx;
	RavEngine::Tween<decimalType, decimalType, decimalType> translate;
	RavEngine::Tween<decimalType, decimalType, decimalType, decimalType> rotate;
	bool ok = false;
};

struct NetTransform : public RavEngine::ComponentWithOwner {
    NetTransform(entity_t owner) : ComponentWithOwner(owner){}
	void UpdateTransform(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin);
};

// stores the information for animating objects on the client
struct PathData: public RavEngine::AutoCTTI {
	float xtiming = RavEngine::Random::get(0.1,0.5), ytiming = RavEngine::Random::get(0.1, 0.5), ztiming = RavEngine::Random::get(0.1, 0.5);
	float offset = RavEngine::Random::get(-10.0, 10.0);
	float scale = 4;
};

struct TweenEntities : public RavEngine::AutoCTTI {

	inline void operator()(float fpsScale, InterpolationTransform& itr) const{
		if (itr.ok) {
			itr.mtx.lock();
			itr.translate.Step(fpsScale);
			itr.rotate.Step(fpsScale);
			itr.mtx.unlock();
		}
	}
};

struct SyncNetTransforms : public RavEngine::AutoCTTI {
	inline void operator()(float scale, NetTransform&, RavEngine::Transform& transform, RavEngine::RPCComponent& rpc) {
		rpc.InvokeServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), RavEngine::NetworkBase::Reliability::Unreliable, Vec3toRaw(transform.GetWorldPosition()), QuatToRaw(transform.GetWorldRotation()));
	}
};
