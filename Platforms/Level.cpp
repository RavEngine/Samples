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
				float matrix[16];
				for(const auto& p : pose){
					for(int r = 0; r < 4; r++){
						float result[4];
						std::memcpy(result,p.cols + r,sizeof(p.cols[r]));
						//_mm_store_ps(result,p.cols[r]);
						std::memcpy(matrix + r*4,result,sizeof(result));
					}
				}
				dbg.DrawSphere(glm::make_mat4(matrix), 0xFF0000FF, 1);
			}
		}
	}
};

void Level::SetupInputs(){
	
	Ref<Entity> camlights = make_shared<Entity>();
	camlights->EmplaceComponent<CameraComponent>()->setActive(true);
	camlights->EmplaceComponent<AmbientLight>()->Intensity = 0.2;
	camlights->transform()->LocalTranslateDelta(vector3(0,0,10));
	
	Ref<Entity> dirlight = make_shared<Entity>();
	dirlight->EmplaceComponent<DirectionalLight>();
	dirlight->transform()->LocalRotateDelta(vector3(glm::radians(45.0),glm::radians(45.0),0));
	
	auto cube = make_shared<Entity>();
	//auto cubemesh = cube->EmplaceComponent<StaticMesh>(make_shared<MeshAsset>("cube.obj"));
	//cubemesh->SetMaterial(make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	cube->transform()->LocalRotateDelta(quaternion(1,1,1,1));
	cube->EmplaceComponent<BoneDebugRenderer>();
	
	//setup animation
	auto skeleton = make_shared<SkeletonAsset>("robot_skeleton.ozz");
	auto animatorComponent = cube->EmplaceComponent<AnimatorComponent>(skeleton);
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
	Spawn(cube);
}
