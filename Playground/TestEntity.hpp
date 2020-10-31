//
//  TestEntity.hpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. All rights reserved.
//

#pragma once

#include "RavEngine/Entity.hpp"
#include "RavEngine/PhysicsBodyComponent.hpp"
#include "RavEngine/WeakRef.hpp"
#include "RavEngine/PhysicsMaterial.hpp"
#include "RavEngine/Material.hpp"
#include "RavEngine/IPhysicsActor.hpp"
#include "RavEngine/ScriptComponent.hpp"
#include "RavEngine/BuiltinMaterials.hpp"
#include <RavEngine/MeshAsset.hpp>
#include <RavEngine/Common3D.hpp>
#include <atomic>

class TestEntityController : public RavEngine::ScriptComponent, public RavEngine::IPhysicsActor {
public:
    void Tick(float scale) override;

    void OnColliderEnter(const WeakRef<RavEngine::PhysicsBodyComponent>&) override;
	void OnColliderExit(const WeakRef<RavEngine::PhysicsBodyComponent>&) override;
	
	void Start() override;
	static std::atomic<int> objectcount;
private:
	RavEngine::color_t color = 0x00FFFFFF;
};

class TestEntity : public RavEngine::Entity, public RavEngine::IPhysicsActor{
protected:
    static Ref<RavEngine::PhysicsMaterial> sharedMat;
    static Ref<RavEngine::DefaultMaterialInstance> sharedMatInst;
	static Ref<RavEngine::MeshAsset> sharedMesh;
public:
    TestEntity();
};
