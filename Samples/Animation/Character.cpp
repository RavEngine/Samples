#include "Character.hpp"
#include <RavEngine/AnimationAsset.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/ChildEntityComponent.hpp>

using namespace RavEngine;
using namespace std;

enum CharAnims {
	Idle,
	Walk,
	Run,
	Fall,
	Jump
};

struct CharacterScript : public ScriptComponent, public RavEngine::IPhysicsActor {
	Ref<AnimatorComponent> animator;
	Ref<RigidBodyDynamicComponent> rigidBody;
	constexpr static decimalType sprintSpeed = 5;

	int16_t groundCounter = 0;

	CharacterScript(const decltype(animator)& a, const decltype(rigidBody)& r) : animator(a), rigidBody(r) {}

	inline bool OnGround() const {
		return groundCounter > 0;	
	}

	void Tick(float fpsScale) final {
		auto velocity = rigidBody->GetLinearVelocity();
		auto movementVel = velocity;
		movementVel.y = 0;

		auto xzspeed = glm::length(movementVel);

		if (OnGround()) {
			if (xzspeed > 0.4 && xzspeed < 1.5) {
				animator->Goto(CharAnims::Walk);
			}
			else if (xzspeed >= 1.5) {
				animator->Goto(CharAnims::Run);
			}
			// not jumping?
			else if (velocity.y < 0.3) {
				animator->Goto(CharAnims::Idle);
			}
		}
		else{
			// falling?
			if (velocity.y < -0.05) {
				animator->Goto(CharAnims::Fall);
			}
		}
		// jumping?
		if (velocity.y > 2) {
			animator->Goto(CharAnims::Jump);
		}

		if (transform()->GetWorldPosition().y < -10) {
			transform()->SetWorldPosition(vector3(0,5,0));
		}
	}

	inline void Move(const vector3& dir, decimalType speedMultiplier) {
		// apply movement only if touching the ground
		if (OnGround()) {
			// move in direction
			auto vec = dir + dir * (speedMultiplier * sprintSpeed);
			vec.y = rigidBody->GetLinearVelocity().y;
			rigidBody->SetLinearVelocity(vec, false);
			rigidBody->SetAngularVelocity(vector3(0, 0, 0), false);
		}
		else {
			// in the air, you can slightly nudge your character in a direction
			rigidBody->AddForce(dir);
		}
		// face direction
		auto rot = glm::quatLookAt(dir, transform()->WorldUp());
		transform()->SetWorldRotation(glm::slerp(transform()->GetWorldRotation(), rot, 0.2));
	}

	inline void Jump() {
		if (OnGround()) {
			auto vel = rigidBody->GetLinearVelocity();
			vel.y = 10;
			rigidBody->SetLinearVelocity(vel,false);
		}
	}


	void OnColliderEnter(const WeakRef<RavEngine::PhysicsBodyComponent>& other) final
	{
		if (other.lock()->filterGroup & FilterLayers::L0) {	// we use filter layer 0 to mark ground
			groundCounter++;
		}
	}

	void OnColliderExit(const WeakRef<RavEngine::PhysicsBodyComponent>& other) final
	{
		if (other.lock()->filterGroup & FilterLayers::L0) {
			groundCounter--;
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
	auto jump_anim = make_shared<AnimationAssetSegment>(all_clips, 160, 163);
	auto fall_anim = make_shared<AnimationAssetSegment>(all_clips, 171, 177);
	auto mesh = make_shared<MeshAssetSkinned>("character_anims.dae", skeleton);
	auto material = make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>());
	material->SetAlbedoColor({1,0.4,0.2,1});

	auto childEntity = make_shared<Entity>();										// I made the animation facing the wrong way
	transform()->AddChild(childEntity->transform());								// so I need a child entity to rotate it back
	childEntity->transform()->LocalRotateDelta(vector3(0, glm::radians(180.f), 0));	// if your animations are the correct orientation you don't need this
	EmplaceComponent<ChildEntityComponent>(childEntity);

	// load the mesh and material onto the character
	auto cubemesh = childEntity->EmplaceComponent<SkinnedMeshComponent>(skeleton, mesh);
	cubemesh->SetMaterial(material);
	childEntity->EmplaceComponent<BoneDebugRenderer>();

	// load the collider and physics settings
	rigidBody = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);
	EmplaceComponent<CapsuleCollider>(0.5, 0.7, make_shared<PhysicsMaterial>(0.0, 0.5, 0.0),vector3(0,0,0),vector3(0,0,glm::radians(90.0)));
	rigidBody->SetAxisLock(RigidBodyDynamicComponent::AxisLock::Angular_X | RigidBodyDynamicComponent::AxisLock::Angular_Z);

	// load the animation
	auto animcomp = childEntity->EmplaceComponent<AnimatorComponent>(skeleton);

	// create the animation state machine
	AnimatorComponent::State
		idle_state{ CharAnims::Idle, idle_anim },
		walk_state{ CharAnims::Walk, walk_anim },
		run_state{ CharAnims::Run, run_anim },
		fall_state{ CharAnims::Fall, fall_anim },
		jump_state{ CharAnims::Jump, jump_anim };

	// some states should not loop
	jump_state.isLooping = false;
	fall_state.isLooping = false;

	// create transitions
	// if a transition between A -> B does not exist, the animation will switch instantly.
	idle_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	idle_state.SetTransition(CharAnims::Fall, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	idle_state.SetTransition(CharAnims::Jump, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	idle_state.SetTransition(CharAnims::Run, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	walk_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	walk_state.SetTransition(CharAnims::Run, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended);
	walk_state.SetTransition(CharAnims::Fall, RavEngine::TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	walk_state.SetTransition(CharAnims::Jump, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	
	run_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended);
	run_state.SetTransition(CharAnims::Fall, RavEngine::TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	run_state.SetTransition(CharAnims::Jump, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	run_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	jump_state.SetTransition(CharAnims::Fall, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	jump_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	jump_state.SetTransition(CharAnims::Run, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	jump_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	fall_state.SetTransition(CharAnims::Idle, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	fall_state.SetTransition(CharAnims::Walk, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	fall_state.SetTransition(CharAnims::Run, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	fall_state.SetTransition(CharAnims::Jump, RavEngine::TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	// add transitions to the animator component
	animcomp->InsertState(walk_state);
	animcomp->InsertState(idle_state);
	animcomp->InsertState(run_state);
	animcomp->InsertState(jump_state);
	animcomp->InsertState(fall_state);

	// initialize the state machine
	// if an entry state is not set before play, your game will crash.
	animcomp->Goto(CharAnims::Idle, true);

	// begin playing the animator controller.
	// animator controllers are asynchronous to your other code
	// so play and pause simply signal the controller to perform an action
	animcomp->Play();

	// this script controls the animation
	script = EmplaceComponent<CharacterScript>(animcomp,rigidBody);
	rigidBody->AddReceiver(script);
}

void Character::Move(const vector3& dir, decimalType speedMultiplier){
	script->Move(dir, speedMultiplier);
}

void Character::Jump()
{
	script->Jump();
}
