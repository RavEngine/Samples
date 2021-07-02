#include "Character.hpp"
#include <RavEngine/AnimationAsset.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>

using namespace RavEngine;
using namespace std;

enum CharAnims {
	Idle,
	Walk
};

Character::Character() {
	// setup animation
	// note: if you are loading multiple instances
	// of an animated character, you will want to load and store
	// the assets separately to avoid unnecessary disk i/o and parsing.
	auto skeleton = make_shared<SkeletonAsset>("character_anims.dae");
	auto all_clips = make_shared<AnimationAsset>("character_anims.dae", skeleton);
	auto walk_anim = make_shared<AnimationAssetSegment>(all_clips, 0, 47);
	auto idle_anim = make_shared<AnimationAssetSegment>(all_clips, 60,120);
	auto mesh = make_shared<MeshAssetSkinned>("character_anims.dae", skeleton);
	auto material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());

	// load the mesh and material onto the character
	auto cubemesh = EmplaceComponent<SkinnedMeshComponent>(skeleton, mesh);
	cubemesh->SetMaterial(material);
	EmplaceComponent<BoneDebugRenderer>();

	// load the collider and physics settings
	EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);
	EmplaceComponent<CapsuleCollider>(1, 1, make_shared<PhysicsMaterial>(0.0, 0.0, 0.0));

	// load the animation
	auto animcomp = EmplaceComponent<AnimatorComponent>(skeleton);

	// create the animation state machine
	AnimatorComponent::State
		idle_state{CharAnims::Idle, idle_anim},
		walk_state{CharAnims::Walk, walk_anim };

	// create transitions
	// if a transition between A -> B does not exist, the animation will switch instantly.
	idle_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	walk_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	animcomp->InsertState(walk_state);
	animcomp->InsertState(idle_state);

	// initialize the state machine
	// if an entry state is not set before play, your game will crash.
	animcomp->Goto(CharAnims::Idle, true);

	// begin playing the animator controller.
	// animator controllers are asynchronous to your other code
	// so play and pause simply signal the controller to perform an action
	animcomp->Play();
}

void Character::SwitchAnimation() {
	GetComponent<AnimatorComponent>().value()->Goto(CharAnims::Walk);
}

void Character::GoToIdle() {
	GetComponent<AnimatorComponent>().value()->Goto(CharAnims::Idle);
}