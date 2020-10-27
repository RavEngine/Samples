//
//  TestEntity.cpp
//  RavEngine_Test
//
//  Copyright © 2020 Ravbug. All rights reserved.
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

using namespace std;
using namespace physx;
using namespace RavEngine;

Ref<RavEngine::PhysicsMaterial> TestEntity::sharedMat;
Ref<RavEngine::DefaultMaterialInstance> TestEntity::sharedMatInst;
Ref<MeshAsset> TestEntity::sharedMesh;

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
	AddComponent<SphereCollider>(new SphereCollider(1,sharedMat));
    //AddComponent<BoxCollider>(new BoxCollider(vector3(1, 1, 1),sharedMat));
	
	if (sharedMesh.isNull()){
		sharedMesh = new MeshAsset("bunny_decimated.obj");
	}

    //default staticmesh
    auto mesh = AddComponent<StaticMesh>(new StaticMesh(sharedMesh));
    if (sharedMatInst.isNull()) {
        sharedMatInst = new DefaultMaterialInstance(Material::Manager::AccessMaterialOfType<DefaultMaterial>());
    }
    mesh->SetMaterial(sharedMatInst);
}

void TestEntityController::Tick(float scale) {

	DebugDraw::DrawSphere(transform()->CalculateWorldMatrix(), color, 1);
    //delete entities below y=-30
    if (transform()->GetWorldPosition().y < -30) {
        Destroy();
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
	auto offset = rand()%10-5;
	transform()->SetWorldPosition(vector3(offset,offset,offset));
}
