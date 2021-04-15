#include "Level.hpp"
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/AnimatorComponent.hpp>
#include <RavEngine/DebugDraw.hpp>

using namespace RavEngine;
using namespace std;

struct BoneDebugRenderer : public RavEngine::IDebugRenderer{
	void DrawDebug(RavEngine::DebugDraw& dbg) const override{
		auto owner =getOwner().lock();
		if (owner){
			if(auto animator = owner->GetComponent<AnimatorComponent>()){
				auto& pose = animator.value()->GetPose();
				for(const auto& p : pose){
					dbg.DrawSphere(p, 0xFFFF00FF, 0.02);
				}
			}
		}
	}
};

void Level::SetupInputs(){
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->setActive(true);
	camlights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	camlights->transform()->LocalTranslateDelta(vector3(0,4,1));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	auto cube = make_shared<Entity>();
	auto cubemesh = cube->EmplaceComponent<StaticMesh>(make_shared<MeshAsset>("astro_maya_2.dae"));
	cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	cube->transform()->LocalTranslateDelta(vector3(0,0,-10));
    cube->EmplaceComponent<BoneDebugRenderer>();
	
	//setup animation
    auto skeleton2 = make_shared<SkeletonAsset>("astro_maya_2.dae");
    auto animatorComponent2 = cube->EmplaceComponent<AnimatorComponent>(skeleton2);
    
    auto clip2 = make_shared<AnimationAsset>("astro_2_anim.dae",skeleton2);
	auto clip = make_shared<AnimationAsset>("astro_maya_2.dae",skeleton2);
	
	//create the blend tree
	auto blendTree = make_shared<AnimBlendTree>();
	AnimBlendTree::Node node(clip2, normalized_vec2(0,1));
	blendTree->InsertNode(0,node);
	blendTree->SetBlendPos(normalized_vec2(0,0.5));
	
	//create the state machine
    
    AnimatorComponent::State
		state2{0,blendTree},
		state3{1,clip};
	
	state3.SetTransition(0, RavEngine::TweenCurves::LinearCurve, 3);
	
    animatorComponent2->InsertState(state2);
	animatorComponent2->InsertState(state3);
    animatorComponent2->Goto(1,true);
    animatorComponent2->Play();
	animatorComponent2->Goto(0);
	
	Spawn(camlights);
	Spawn(dirlight);
	Spawn(cube);
}
