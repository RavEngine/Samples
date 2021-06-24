#pragma once
#include <RavEngine/Component.hpp>
#include <RavEngine/AccessType.hpp>
#include <RavEngine/QueryIterator.hpp>
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
	float xtiming = 0.2, ytiming = 0.5, ztiming = 0.01;
	float offset = RavEngine::Random::get(-5, 5);
	float scale = 4;
};

struct TweenEntities : public RavEngine::AutoCTTI {

	inline constexpr auto QueryTypes() const {
		return RavEngine::QueryIteratorAND<InterpolationTransform>();
	}

	inline void Tick(float fpsScale, RavEngine::AccessReadWrite<InterpolationTransform> it) {
		auto itr = it.get();
		if (itr->ok) {
			itr->mtx.lock();
			itr->translate.step(fpsScale);
			itr->rotate.step(fpsScale);
			itr->mtx.unlock();
		}
	}
};

struct SyncNetTransforms : public RavEngine::AutoCTTI {
	inline void Tick(float scale, RavEngine::AccessRead<NetTransform>, RavEngine::AccessRead<RavEngine::Transform> tr, RavEngine::AccessReadWrite<RavEngine::RPCComponent> r) {
		auto transform = tr.get();
		auto rpc = r.get();

		rpc->InvokeServerRPC(RavEngine::to_underlying(RPCs::UpdateTransform), RavEngine::NetworkBase::Reliability::Unreliable, vec3toRaw(transform->GetWorldPosition()), quatToRaw(transform->GetWorldRotation()));
	}

	inline constexpr auto QueryTypes() const {
		return RavEngine::QueryIteratorAND<NetTransform, RavEngine::Transform, RavEngine::RPCComponent>();
	}
};