#include "Character.hpp"
#include <RavEngine/AnimationAsset.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>

using namespace RavEngine;
using namespace std;

enum CharAnims {
	Idle,
	Walk,
	Run
};

struct CharacterScript : public ScriptComponent {
	Ref<AnimatorComponent> animator;
	Ref<RigidBodyDynamicComponent> rigidBody;

	CharacterScript(const decltype(animator)& a, const decltype(rigidBody)& r) : animator(a), rigidBody(r) {}

	void Tick(float fpsScale) final {
		auto velocity = glm::length(rigidBody->GetLinearVelocity());
		if (velocity > 0.8 && velocity < 1.0) {
			animator->Goto(CharAnims::Walk);
		}
		else if (velocity >= 1.0) {
			animator->Goto(CharAnims::Run);
		}
		else {
			animator->Goto(CharAnims::Idle);
		}
	}
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
	auto run_anim = make_shared<AnimationAssetSegment>(all_clips, 131, 149);
	auto mesh = make_shared<MeshAssetSkinned>("character_anims.dae", skeleton);
	auto material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());

	// load the mesh and material onto the character
	auto cubemesh = EmplaceComponent<SkinnedMeshComponent>(skeleton, mesh);
	cubemesh->SetMaterial(material);
	EmplaceComponent<BoneDebugRenderer>();

	// load the collider and physics settings
	rigidBody = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);
	EmplaceComponent<CapsuleCollider>(0.5, 0.7, make_shared<PhysicsMaterial>(0.0, 0.5, 0.0),vector3(0,0,0),vector3(0,0,glm::radians(90.0)));
	rigidBody->SetAxisLock(RigidBodyDynamicComponent::AxisLock::Angular_X | RigidBodyDynamicComponent::AxisLock::Angular_Z);

	// load the animation
	auto animcomp = EmplaceComponent<AnimatorComponent>(skeleton);

	// create the animation state machine
	AnimatorComponent::State
		idle_state{ CharAnims::Idle, idle_anim },
		walk_state{ CharAnims::Walk, walk_anim },
		run_state{ CharAnims::Run, run_anim };

	// create transitions
	// if a transition between A -> B does not exist, the animation will switch instantly.
	idle_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	walk_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	walk_state.SetTransition(CharAnims::Run, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended);
	run_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended);

	animcomp->InsertState(walk_state);
	animcomp->InsertState(idle_state);
	animcomp->InsertState(run_state);

	// initialize the state machine
	// if an entry state is not set before play, your game will crash.
	animcomp->Goto(CharAnims::Idle, true);

	// begin playing the animator controller.
	// animator controllers are asynchronous to your other code
	// so play and pause simply signal the controller to perform an action
	animcomp->Play();

	// this script controls the animation
	EmplaceComponent<CharacterScript>(animcomp,rigidBody);
}

void Character::Move(const vector3& dir, decimalType speedMultiplier){
	// move in direction
	rigidBody->SetLinearVelocity(dir * (speedMultiplier * sprintSpeed), false);
	// face direction
	auto rot = glm::quatLookAt(dir, transform()->WorldUp());
	transform()->SetWorldRotation(rot);
}
