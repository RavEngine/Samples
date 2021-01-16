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

using namespace std;
using namespace physx;
using namespace RavEngine;

Ref<RavEngine::PhysicsMaterial> TestEntity::sharedMat;
Ref<RavEngine::PBRMaterialInstance> TestEntity::sharedMatInst;
Ref<MeshAsset> TestEntity::sharedMesh;
atomic<int> TestEntityController::objectcount;

TestEntity::TestEntity() : Entity(){

    //attach the script
    auto script = AddComponent<TestEntityController>(make_shared<TestEntityController>());

    //set the filter layers
    auto r = AddComponent<RigidBodyDynamicComponent>(make_shared<RigidBodyDynamicComponent>(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1));
    r->AddReceiver(script.get());

    //add a box collision to the PhysX component
    if (!sharedMat) {
        sharedMat = make_shared<PhysicsMaterial>(0.5, 0.5, 0.5);
    }
	AddComponent<CapsuleCollider>(make_shared<CapsuleCollider>(1,1,sharedMat));
    //AddComponent<BoxCollider>(new BoxCollider(vector3(1, 1, 1),sharedMat));
	
	if (!sharedMesh){
		sharedMesh = make_shared<MeshAsset>("bunny_decimated.obj");
	}

    //default staticmesh
    auto mesh = AddComponent<StaticMesh>(make_shared<StaticMesh>(sharedMesh));
    if (!sharedMatInst) {
        sharedMatInst = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
    }
    mesh->SetMaterial(sharedMatInst);
}

void TestEntityController::Tick(float scale) {

	GetEntity()->GetComponent<PhysicsCollider>()->DebugDraw(contactCount == 0 ? 0x0000FFFF : 0xFFFFFFFF);
    if (transform()->GetWorldPosition().y < -40) {
        Destroy();
        objectcount--;
    }
}

void TestEntityController::OnColliderEnter(const WeakRef<PhysicsBodyComponent>& other)
{
	contactCount++;
}

void TestEntityController::OnColliderExit(const WeakRef<PhysicsBodyComponent>& other){
	contactCount--;
}

void TestEntityController::Start(){
	transform()->SetWorldPosition(vector3(rand()%10-5,rand()%10-5,rand()%10-5));
    objectcount++;
}
