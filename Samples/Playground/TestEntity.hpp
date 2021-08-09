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
#include <RavEngine/RPCComponent.hpp>
#include <RavEngine/Debug.hpp>
#include <uuids.h>
#include <atomic>
#include <RavEngine/SyncVar.hpp>

//RPC IDs
struct TestEntityCodes {
	enum {
		ServerRPC = 0,
		ClientRPC,
	};
};


class TestEntityController : public RavEngine::ScriptComponent, public RavEngine::IPhysicsActor {
public:
    void Tick(float scale) override;

    void OnColliderEnter(const WeakRef<RavEngine::PhysicsBodyComponent>&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) override;
	void OnColliderExit(const WeakRef<RavEngine::PhysicsBodyComponent>&, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) override;
	
	void Start() override;
	static std::atomic<int> objectcount;
	std::atomic<int> contactCount;

	RavEngine::SyncVar<float> my_x;
};

struct TestEntityRPCs : public RavEngine::Component, public RavEngine::Queryable<TestEntityRPCs> {
	void ServerRPCTest(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin) {
		auto A = upk.get<int>().value();
		auto B = upk.get<float>().value();
		RavEngine::Debug::Log("Server message! Values are {} and {}", A, B);
	}

	void ClientRPCTest(RavEngine::RPCMsgUnpacker& upk, HSteamNetConnection origin) {
		//auto A = upk.get<int>().value();
		//auto B = upk.get<float>().value();
		//RavEngine::Debug::Log("Client message! Values are {} and {}", A, B);

		////get the value in collision, and send an RPC back to the server with the same number again
		//getOwner().lock()->GetComponent<RavEngine::RPCComponent>().value()->InvokeServerRPC(TestEntityCodes::ServerRPC,RavEngine::NetworkBase::Reliability::Reliable,A,B);
	}
};

class TestEntity : public RavEngine::Entity, public RavEngine::IPhysicsActor, public RavEngine::NetworkReplicable {
protected:
    static Ref<RavEngine::PhysicsMaterial> sharedMat;
    static Ref<RavEngine::PBRMaterialInstance> sharedMatInst;
	static Ref<RavEngine::MeshAsset> sharedMesh;
	void CommonInit();
public:
    TestEntity();
	TestEntity(const uuids::uuid&);	//for netspawn

	RavEngine::ctti_t NetTypeID() const override {
		return RavEngine::CTTI<TestEntity>();
	}
};

struct TestEntityDebugRenderer : public RavEngine::IDebugRenderer{
	void DrawDebug(RavEngine::DebugDraw& dbg) const override{
		auto owner = std::static_pointer_cast<TestEntity>(getOwner().lock());
		if (owner){
			auto script = owner->GetComponent<TestEntityController>().value();
			owner->GetComponent<RavEngine::PhysicsCollider>().value()->DebugDraw(dbg, script->contactCount == 0 ? 0x0000FFFF : 0xFFFFFFFF);
		}
	}
};
