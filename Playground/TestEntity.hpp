//
//  TestEntity.hpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug.
//

#pragma once

#include "RavEngine/Entity.hpp"
#include "RavEngine/PhysicsCollider.hpp"
#include "RavEngine/PhysicsBodyComponent.hpp"
#include "RavEngine/WeakRef.hpp"
#include "RavEngine/PhysicsMaterial.hpp"
#include "RavEngine/Material.hpp"
#include "RavEngine/IPhysicsActor.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include "RavEngine/BuiltinMaterials.hpp"
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/Common3D.hpp>
#include <RavEngine/DebugDraw.hpp>
#include <RavEngine/NetworkReplicable.hpp>
#include <RavEngine/CTTI.hpp>
#include <atomic>

class TestEntityController : public RavEngine::ScriptComponent, public RavEngine::IPhysicsActor {
public:
    void Tick(float scale) override;

    void OnColliderEnter(const WeakRef<RavEngine::PhysicsBodyComponent>&) override;
	void OnColliderExit(const WeakRef<RavEngine::PhysicsBodyComponent>&) override;
	
	void Start() override;
	static std::atomic<int> objectcount;
	std::atomic<int> contactCount;

	
};

class TestEntity : public RavEngine::Entity, public RavEngine::IPhysicsActor, public RavEngine::NetworkReplicable {
protected:
    static Ref<RavEngine::PhysicsMaterial> sharedMat;
    static Ref<RavEngine::PBRMaterialInstance> sharedMatInst;
	static Ref<RavEngine::MeshAsset> sharedMesh;
public:
    TestEntity();

	RavEngine::ctti_t NetTypeID() const override {
		return RavEngine::CTTI<TestEntity>;
	}
};

struct TestEntityDebugRenderer : public RavEngine::IDebugRenderer{
	void DrawDebug(RavEngine::DebugDraw& dbg) const override{
		auto owner = std::static_pointer_cast<TestEntity>(getOwner().lock());
		if (owner){
			auto script = owner->GetComponent<TestEntityController>();
			owner->GetComponent<RavEngine::PhysicsCollider>()->DebugDraw(dbg, script->contactCount == 0 ? 0x0000FFFF : 0xFFFFFFFF);
		}
	}
};
