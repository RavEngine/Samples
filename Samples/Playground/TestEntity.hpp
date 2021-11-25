//
//  TestEntity.hpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug.
//

#pragma once

#include "RavEngine/GameObject.hpp"
#include "RavEngine/PhysicsCollider.hpp"
#include "RavEngine/PhysicsBodyComponent.hpp"
#include "RavEngine/WeakRef.hpp"
#include "RavEngine/PhysicsMaterial.hpp"
#include "RavEngine/Material.hpp"
#include "RavEngine/PhysicsCallback.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include "RavEngine/BuiltinMaterials.hpp"
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/Common3D.hpp>
#include <RavEngine/DebugDrawer.hpp>
#include <RavEngine/NetworkReplicable.hpp>
#include <RavEngine/CTTI.hpp>
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Debug.hpp>
#include <uuids.h>
#include <atomic>
#include <RavEngine/Queryable.hpp>

struct TestEntityController : public RavEngine::ScriptComponent, public RavEngine::Queryable<TestEntityController,ScriptComponent> {
	using RavEngine::Queryable<TestEntityController, ScriptComponent>::GetQueryTypes;
	TestEntityController(entity_t owner) : ScriptComponent(owner) {}
    void Tick(float scale) override;

	void OnColliderEnter(RavEngine::PhysicsBodyComponent&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) {
		contactCount++;
	}
	void OnColliderExit(RavEngine::PhysicsBodyComponent&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) {
		contactCount--;
	}
	
	static std::atomic<int> objectcount;
	std::atomic<int> contactCount;
};

class TestEntity : public RavEngine::GameObject, public RavEngine::PhysicsCallback{
protected:
    static Ref<RavEngine::PhysicsMaterial> sharedMat;
    static Ref<RavEngine::PBRMaterialInstance> sharedMatInst;
	void CommonInit();
public:
	void Create() {
		GameObject::Create();
		CommonInit();
	}
};
