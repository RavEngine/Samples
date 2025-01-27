#pragma once

#include <RavEngine/GameObject.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/ComponentWithOwner.hpp>

namespace RavEngine {
	class PhysicsBodyComponent;
	struct ContactPairPoint;
	class AudioAsset;
}

//marker for querying
struct PuckComponent : public RavEngine::ComponentWithOwner{
    PuckComponent(RavEngine::Entity owner) : ComponentWithOwner(owner){}
};

struct PuckScript : public RavEngine::ScriptComponent, public RavEngine::Queryable<PuckScript,RavEngine::ScriptComponent>{
	double lastSoundTime = 0;

    using RavEngine::Queryable<PuckScript,RavEngine::ScriptComponent>::GetQueryTypes;
    
    RavEngine::Array<Ref<RavEngine::AudioAsset>,4> sounds;
	PuckScript(RavEngine::Entity owner);
	void Tick(float scale) override{}
	void OnColliderEnter(RavEngine::PhysicsBodyComponent&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints);
};

class Puck : public RavEngine::GameObject{
public:
    static Ref<RavEngine::PBRMaterialInstance> material;
	void Create();
};
