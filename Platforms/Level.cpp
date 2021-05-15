#include "Level.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/DebugDraw.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>

using namespace RavEngine;
using namespace std;

struct BoneDebugRenderer : public RavEngine::IDebugRenderer{
	void DrawDebug(RavEngine::DebugDraw& dbg) const override{
		auto owner =getOwner().lock();
		if (owner){
			if(auto animator = owner->GetComponent<AnimatorComponent>()){
				auto& pose = animator.value()->GetPose();
				for(const auto& p : pose){
					dbg.DrawSphere(p, 0xFFFF00FF, 0.1);
				}
			}
		}
	}
};

void Level::SetupInputs(){
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->setActive(true);
	camlights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	camlights->transform()->LocalTranslateDelta(vector3(3,0.5,6));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	//setup animation
	auto skeleton = make_shared<SkeletonAsset>("simplerig3.dae");
	
	cube = make_shared<Entity>();
	auto cubemesh = cube->EmplaceComponent<SkinnedMeshComponent>(skeleton,make_shared<MeshAssetSkinned>("simplerig3.dae",skeleton));
	cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	cube->transform()->LocalTranslateDelta(vector3(3,0,0));
	cube->EmplaceComponent<BoneDebugRenderer>();
	
	auto animatorComponent2 = cube->EmplaceComponent<AnimatorComponent>(skeleton);
	
	auto clip2 = make_shared<AnimationAsset>("simplerig3.dae",skeleton);
	auto clip = make_shared<AnimationAsset>("simplerig3.dae",skeleton);
	
	//create the blend tree
	auto blendTree = make_shared<AnimBlendTree>();
	AnimBlendTree::Node node(clip2, normalized_vec2(0,1));
	blendTree->InsertNode(0,node);
	blendTree->SetBlendPos(normalized_vec2(0,0.5));
	
	//create the state machine
	
	AnimatorComponent::State
	state2{0,blendTree},
	state3{1,clip};
	
	state3.SetTransition(0, RavEngine::TweenCurves::LinearCurve, 3,AnimatorComponent::State::Transition::TimeMode::BeginNew);
	//state2.isLooping = false;
	
	animatorComponent2->InsertState(state2);
	animatorComponent2->InsertState(state3);
	animatorComponent2->Goto(1,true);
	animatorComponent2->Play();
	animatorComponent2->Goto(0);
	
	Spawn(camlights);
	Spawn(dirlight);
	Spawn(cube);
}

void Level::posttick(float scale){
	float rotamt = glm::radians(scale * 0.1);
	cube->transform()->LocalRotateDelta(vector3(rotamt,rotamt,-rotamt));
}
