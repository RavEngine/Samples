#include "Level.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/DebugDraw.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Utilities.hpp>

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
	camlights->transform()->LocalTranslateDelta(vector3(0,0.5,6));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	//setup animation
	auto skeleton = make_shared<SkeletonAsset>("simplerig3.dae");
	auto clip2 = make_shared<AnimationAsset>("simplerig3.dae",skeleton);
	auto clip = make_shared<AnimationAsset>("simplerig3.dae",skeleton);
	auto mesh = make_shared<MeshAssetSkinned>("simplerig3.dae",skeleton);
	auto material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	
	for(int i = 0; i < 10; i++){
		auto cube = make_shared<Entity>();
		auto cubemesh = cube->EmplaceComponent<SkinnedMeshComponent>(skeleton,mesh);
		cubemesh->SetMaterial(material);
		cube->transform()->LocalTranslateDelta(vector3(Random::get(-3,3),Random::get(-3,3),Random::get(-3,0)));
		cube->EmplaceComponent<BoneDebugRenderer>();
		
		auto animatorComponent2 = cube->EmplaceComponent<AnimatorComponent>(skeleton);
		
		//create the blend tree
		auto blendTree = make_shared<AnimBlendTree>();
		AnimBlendTree::Node node(clip2, normalized_vec2(0,1));
		blendTree->InsertNode(0,node);
		blendTree->SetBlendPos(normalized_vec2(0,0.5));
		
		//create the state machine
		
		AnimatorComponent::State
		state2{0,blendTree},
		state3{1,clip};
		state2.speed = Random::get(0.1f,3.f);
		state3.speed = Random::get(0.1f,3.f);
				
		state3.SetTransition(0, RavEngine::TweenCurves::LinearCurve, 3,AnimatorComponent::State::Transition::TimeMode::BeginNew);
		//state2.isLooping = false;
		
		animatorComponent2->InsertState(state2);
		animatorComponent2->InsertState(state3);
		animatorComponent2->Goto(1,true);
		animatorComponent2->Play();
		animatorComponent2->Goto(0);
		
		cubes.push_back(cube);
		Spawn(cube);
	}
	
	
	Spawn(camlights);
	Spawn(dirlight);
}

void Level::posttick(float scale){
	float rotamt = glm::radians(scale * 0.1);
	for(const auto& cube : cubes){
		cube->transform()->LocalRotateDelta(vector3(rotamt,rotamt,-rotamt));
		rotamt += 0.001;
		if(App::currentTime() > 5 && App::currentTime() < 10){
			cube->GetComponent<AnimatorComponent>().value()->Pause();
		}
		if(App::currentTime() > 10){
			cube->GetComponent<AnimatorComponent>().value()->Play();
		}
	}
}
