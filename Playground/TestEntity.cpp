//
//  TestEntity.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. 
//

#include "TestEntity.hpp"
#include "SkateSystem.h"
#include "RavEngine/PhysicsLinkSystem.hpp"
#include "RavEngine/PhysicsCollider.hpp"
#include <PxMaterial.h>
#include "RavEngine/PhysicsSolver.hpp"
#include <iostream>
#include "RavEngine/StaticMesh.hpp"
#include <RavEngine/Debug.hpp>
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
    auto script = AddComponent<TestEntityController>(new TestEntityController());

    //set the filter layers
    auto r = AddComponent<RigidBodyDynamicComponent>(new RigidBodyDynamicComponent(FilterLayers::L0,FilterLayers::L0 | FilterLayers::L1));
    r->AddReceiver(script.get());

    //add a box collision to the PhysX component
    if (sharedMat.isNull()) {
        sharedMat = new PhysicsMaterial(0.5, 0.5, 0.5);
    }
	AddComponent<CapsuleCollider>(new CapsuleCollider(1,1,sharedMat));
    //AddComponent<BoxCollider>(new BoxCollider(vector3(1, 1, 1),sharedMat));
	
	if (sharedMesh.isNull()){
		sharedMesh = new MeshAsset("bunny_decimated.obj");
	}

    //default staticmesh
    auto mesh = AddComponent<StaticMesh>(new StaticMesh(sharedMesh));
    if (sharedMatInst.isNull()) {
        sharedMatInst = new PBRMaterialInstance(Material::Manager::AccessMaterialOfType<PBRMaterial>());
    }
    mesh->SetMaterial(sharedMatInst);
}

void TestEntityController::Tick(float scale) {
	
	GetEntity()->Components().GetComponent<PhysicsCollider>()->DebugDraw(color);
    if (transform()->GetWorldPosition().y < -30) {
        Destroy();
        objectcount--;
    }
}

void TestEntityController::OnColliderEnter(const WeakRef<PhysicsBodyComponent>& other)
{
	color = 0xFFFFFFFF;
}

void TestEntityController::OnColliderExit(const WeakRef<PhysicsBodyComponent>& other){
	color = 0x0000FFFF;
}

void TestEntityController::Start(){
	transform()->SetWorldPosition(vector3(rand()%10-5,rand()%10-5,rand()%10-5));
    objectcount++;
}
