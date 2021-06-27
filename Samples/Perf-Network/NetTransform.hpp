#pragma once
#include <RavEngine/Component.hpp>
#include <RavEngine/Queryable.hpp>
#include <RavEngine/Tween.hpp>
#include <RavEngine/RPCComponent.hpp>

enum class RPCs {
	UpdateTransform,
};

struct InterpolationTransform : public RavEngine::Component, public RavEngine::Queryable<InterpolationTransform> {
	RavEngine::SpinLock mtx;
	RavEngine::Tween<decimalType, decimalType, decimalType> translate;
	RavEngine::Tween<decimalType, decimalType, decimalType, decimalType> rotate;
	bool ok = false;
};

struct NetTransform : public RavEngine::Component, public RavEngine::Queryable<NetTransform> {
	void UpdateTransform(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin);
};

// stores the information for animating objects on the client
struct PathData : public RavEngine::Component, public RavEngine::Queryable<PathData> {
	float xtiming = RavEngine::Random::get(0.1,0.5), ytiming = RavEngine::Random::get(0.1, 0.5), ztiming = RavEngine::Random::get(0.1, 0.5);
	float offset = RavEngine::Random::get(-10.0, 10.0);
	float scale = 4;
};

struct TweenEntities : public RavEngine::AutoCTTI {

	inline void Tick(float fpsScale, Ref<InterpolationTransform> itr) {
		if (itr->ok) {
			itr->mtx.lock();
			itr->translate.step(fpsScale);
			itr->rotate.step(fpsScale);
			itr->mtx.unlock();
		}
	}
};

struct SyncNetTransforms : public RavEngine::AutoCTTI {
	inline void Tick(float scale, Ref<NetTransform>, Ref<RavEngine::Transform> transform, Ref<RavEngine::RPCComponent> rpc) {
		rpc->InvokeServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), RavEngine::NetworkBase::Reliability::Unreliable, vec3toRaw(transform->GetWorldPosition()), quatToRaw(transform->GetWorldRotation()));
	}
};