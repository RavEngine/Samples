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
#include <RavEngine/MeshCollection.hpp>

using namespace std;
using namespace physx;
using namespace RavEngine;

STATIC(TestEntity::sharedMat);
STATIC(TestEntity::sharedMatInst);
STATIC(TestEntityController::objectcount);

void TestEntity::CommonInit(){
	
	//default staticmesh
    if (!sharedMatInst) {
        sharedMatInst = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
    }
	auto mesh = EmplaceComponent<StaticMesh>(MeshCollectionStaticManager::Get("bunny_decimated"), sharedMatInst);

    auto& script = EmplaceComponent<TestEntityController>();
	auto& r = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);

	auto handler = RavEngine::New<PhysicsCallback>();
	ComponentHandle<TestEntityController> scripthandle(this);
	handler->OnColliderEnter = [scripthandle](RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) mutable{
		scripthandle->OnColliderEnter(other,contactPoints,numContactPoints);
	};

	handler->OnColliderExit = [scripthandle](RavEngine::PhysicsBodyComponent& other, const RavEngine::ContactPairPoint* contactPoints, size_t numContactPoints) mutable{
		scripthandle->OnColliderExit(other,contactPoints,numContactPoints);
	};

	r.AddReceiver(handler);

	//add a box collision to the PhysX component
	if (!sharedMat) {
		sharedMat = RavEngine::New<PhysicsMaterial>(0.5, 0.5, 0.5);
	}
	r.EmplaceCollider<CapsuleCollider>(1.f, 1.f, sharedMat);

	r.setDynamicsWorldPose(vector3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5), GetTransform().GetWorldRotation());

	script.objectcount++;
}


void TestEntityController::Tick(float scale) {

    if (GetOwner().GetTransform().GetWorldPosition().y < -40) {
		auto e = GetOwner();
        assert(markedForDeletion == false);
        markedForDeletion = true;
		GetApp()->DispatchMainThread([e]() mutable {
			e.Destroy();
			objectcount--;
		});
       
    }
}
