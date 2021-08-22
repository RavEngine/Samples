//
//  TestEntity.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. 
//

#include "TestEntity.hpp"
#include "RavEngine/PhysicsLinkSystem.hpp"
#include "RavEngine/PhysicsCollider.hpp"
#include <PxMaterial.h>
#include "RavEngine/PhysicsSolver.hpp"
#include <iostream>
#include "RavEngine/StaticMesh.hpp"
#include <RavEngine/mathtypes.hpp>
#include <RavEngine/NetworkIdentity.hpp>
#include <RavEngine/RPCComponent.hpp>

using namespace std;
using namespace physx;
using namespace RavEngine;

Ref<RavEngine::PhysicsMaterial> TestEntity::sharedMat;
Ref<RavEngine::PBRMaterialInstance> TestEntity::sharedMatInst;
Ref<MeshAsset> TestEntity::sharedMesh;
atomic<int> TestEntityController::objectcount;

void TestEntity::CommonInit(){
	if (!sharedMesh){
		sharedMesh = make_shared<MeshAsset>("bunny_decimated.obj");
	}
	
	//default staticmesh
	auto mesh = EmplaceComponent<StaticMesh>(sharedMesh);
	if (!sharedMatInst) {
		sharedMatInst = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	}
	mesh->SetMaterial(sharedMatInst);

	//RPC component
	auto rpc = EmplaceComponent<RPCComponent>();
	auto rpcFuncs = EmplaceComponent<TestEntityRPCs>();
	rpc->RegisterServerRPC(TestEntityCodes::ServerRPC,rpcFuncs,&TestEntityRPCs::ServerRPCTest, RPCComponent::Directionality::Bidirectional);	//clients can run this even if they are not owners of the object
	rpc->RegisterClientRPC(TestEntityCodes::ClientRPC, rpcFuncs, &TestEntityRPCs::ClientRPCTest);
}

TestEntity::TestEntity() : Entity(){

    //attach the script
    auto script = EmplaceComponent<TestEntityController>();

    //set the filter layers
    auto r = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1);
    r->AddReceiver(script);

    //add a box collision to the PhysX component
    if (!sharedMat) {
        sharedMat = make_shared<PhysicsMaterial>(0.5, 0.5, 0.5);
    }
    EmplaceComponent<CapsuleCollider>(1,1,sharedMat);
	
	CommonInit();
	
	EmplaceComponent<TestEntityDebugRenderer>();
	
	EmplaceComponent<NetworkIdentity>();
}

TestEntity::TestEntity(const uuids::uuid& uuid) : Entity(){
	CommonInit();
	
	EmplaceComponent<NetworkIdentity>(uuid);
}

void TestEntityController::Tick(float scale) {

    if (GetTransform()->GetWorldPosition().y < -40) {
        Destroy();
        objectcount--;
    }
	my_x = GetTransform()->GetWorldPosition().x;
}

void TestEntityController::OnColliderEnter(const WeakRef<PhysicsBodyComponent>& other, const ContactPairPoint* contactPoints, size_t numContactPoints)
{
	auto pos = other.lock()->GetOwner().lock()->GetTransform()->GetWorldPosition();
	GetOwner().lock()->GetComponent<RPCComponent>().value()->InvokeClientRPC(TestEntityCodes::ClientRPC,RavEngine::NetworkBase::Reliability::Reliable,(int)pos.x,(float)pos.z);
	contactCount++;
}

void TestEntityController::OnColliderExit(const WeakRef<PhysicsBodyComponent>& other, const ContactPairPoint* contactPoints, size_t numContactPoints){
	contactCount--;
}

void TestEntityController::Start(){
	GetTransform()->SetWorldPosition(vector3(rand()%10-5,rand()%10-5,rand()%10-5));
    objectcount++;
}
