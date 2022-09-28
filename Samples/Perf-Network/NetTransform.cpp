#include "NetTransform.hpp"

using namespace std;
using namespace RavEngine;

void NetTransform::UpdateTransform(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin)
{
	auto owner = GetOwner();
	// update server's copy of this transform
	auto& itr = owner.GetComponent<InterpolationTransform>();
	itr.mtx.lock();
	std::optional<RawVec3> td;
	if ((td = upk.Get<RawVec3>())) {
		auto currentpos = owner.GetTransform().GetLocalPosition();
		RavEngine::Debug::Assert(!std::isnan(currentpos.x), "CurrentPos was NaN!");
		RavEngine::Debug::Assert(!std::isnan(td.value()[0]), "NetworkPos was NaN!");
		// create the tween
		// another system will tick this tween
		itr.translate = decltype(itr.translate)([=](decimalType x, decimalType y, decimalType z) mutable {
			if (isnan(x) || isnan(y) || isnan(z)) {		//sometimes the value is NaN???
				return;
			}
			owner.GetTransform().SetLocalPosition(vector3(x, y, z));
			}, currentpos.x, currentpos.y, currentpos.z);
		auto t = td.value();
		itr.translate.AddKeyframe(0.1, RavEngine::TweenCurves::LinearCurve, t[0], t[1], t[2]);
	}
	std::optional<RawQuat> qd;
	if ((qd = upk.Get<RawQuat>())) {
		auto currentRot = owner.GetTransform().GetLocalRotation();

		itr.rotate = decltype(itr.rotate)([=](decimalType w, decimalType x, decimalType y, decimalType z) mutable{
			if (isnan(w) || isnan(x) || isnan(y) || isnan(z)) {
				return;
			}
			owner.GetTransform().SetLocalRotation(quaternion(w, x, y, z));
			}, currentRot.w, currentRot.x, currentRot.y, currentRot.z);
		auto r = qd.value();
		itr.rotate.AddKeyframe(0.1, RavEngine::TweenCurves::LinearCurve, r[0], r[1], r[2], r[3]);
	}
	itr.ok = true;
	itr.mtx.unlock();

	// now RPC all the clients except the sender of this message to update their copy of this object
	// as well
	auto& rpc = owner.GetComponent<RavEngine::RPCComponent>();
    if (GetApp()->networkManager.IsServer() && td && qd){
        rpc.InvokeClientRPCToAllExcept(RavEngine::to_underlying(RPCs::UpdateTransform), origin, RavEngine::NetworkBase::Reliability::Unreliable, td.value(), qd.value());
    }
}
