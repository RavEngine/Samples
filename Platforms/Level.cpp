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
	camlights->transform()->LocalTranslateDelta(vector3(0,0,1));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	auto animatedObject = make_shared<Entity>();
	auto cube = make_shared<Entity>();
	auto cubemesh = cube->EmplaceComponent<StaticMesh>(make_shared<MeshAsset>("astro_maya.dae"));
	cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	cube->transform()->LocalTranslateDelta(vector3(0,0,-10));
	animatedObject->EmplaceComponent<BoneDebugRenderer>();
	animatedObject->transform()->LocalRotateDelta(quaternion(1,1,1,-1));
	
	//setup animation
	auto skeleton = make_shared<SkeletonAsset>("robot_skeleton.ozz");
    auto skeleton2 = make_shared<SkeletonAsset>("astro_maya.dae");
	auto animatorComponent = animatedObject->EmplaceComponent<AnimatorComponent>(skeleton);
    auto animatorComponent2 = cube->EmplaceComponent<AnimatorComponent>(skeleton2);
	auto clip = make_shared<AnimationAsset>("robot_animation.ozz");
	
	//create the blend tree
	auto blendTree = make_shared<AnimBlendTree>();
	AnimBlendTree::Node node(clip, normalized_vec2(0,1));
	blendTree->InsertNode(0,node);
	blendTree->SetBlendPos(normalized_vec2(0,1));
	
	//create the state machine
	AnimatorComponent::State state{0,blendTree};
	animatorComponent->InsertState(state);
	animatorComponent->Goto(0,true);

	animatorComponent->Play();
	
	Spawn(camlights);
	Spawn(dirlight);
	Spawn(animatedObject);
	Spawn(cube);
}
