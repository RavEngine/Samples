#include "Character.hpp"
#include <RavEngine/AnimationAsset.hpp>
#include <RavEngine/MeshAssetSkinned.hpp>
#include <RavEngine/BuiltinMaterials.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/ScriptComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/PhysicsBodyComponent.hpp>
#include <RavEngine/SkinnedMeshComponent.hpp>
#include <RavEngine/Constraint.hpp>
#include <RavEngine/PhysicsSolver.hpp>

using namespace RavEngine;
using namespace std;

// show green cubes to diagnose transform hierarchy issues
#define TRANSFORM_DEBUG 0

enum CharAnims {
	Idle,
	Walk,
	Run,
	Fall,
	Jump,
	PoundBegin,
	InPound,
	PoundEnd
};


	
bool CharacterScript::OnGround() const {
	return groundCounter > 0;	
}

void CharacterScript::Tick(float fpsScale) {
	switch (animator->GetCurrentState()) {
		case CharAnims::PoundBegin:
		case CharAnims::InPound:
		case CharAnims::PoundEnd:
			// hit the ground? go to poundEnd
			if (OnGround() && animator->GetCurrentState() != PoundEnd) {
				animator->Goto(PoundEnd);
			}
			break;
		default: {
			auto velocity = rigidBody->GetLinearVelocity();
			auto movementVel = velocity;
			movementVel.y = 0;

			auto xzspeed = glm::length(movementVel);

			if (OnGround()) {
				if (xzspeed > 0.4 && xzspeed < 2.2) {
					animator->Goto(CharAnims::Walk);
				}
				else if (xzspeed >= 2.2) {
					animator->Goto(CharAnims::Run);
				}
				// not jumping?
				else if (velocity.y < 0.3) {
					animator->Goto(CharAnims::Idle);
				}
			}
			else {
				// falling and not in pound animation?
				if (velocity.y < -0.05) {
					switch (animator->GetCurrentState()) {
					case CharAnims::PoundBegin:
					case CharAnims::PoundEnd:
					case CharAnims::InPound:
						break;
					default:
						animator->Goto(CharAnims::Fall);
					}
				}
			}
			// jumping?
			if (velocity.y > 5) {
				animator->Goto(CharAnims::Jump);
			}
		}
	}
	if (GetOwner().GetTransform().GetWorldPosition().y < -10) {
		rigidBody->setDynamicsWorldPose(vector3(0, 5, 0), GetOwner().GetTransform().GetLocalRotation());
		//GetTransform().SetWorldPosition(vector3(0, 5, 0));
	}
}

void CharacterScript::Move(const vector3& dir, decimalType speedMultiplier) {
	if (controlsEnabled) {
		// apply movement only if touching the ground
		if (OnGround()) {
			// move in direction
			auto vec = dir * walkSpeed + dir * (speedMultiplier * sprintSpeed);
			vec.y = rigidBody->GetLinearVelocity().y;
			rigidBody->SetLinearVelocity(vec, false);
			rigidBody->SetAngularVelocity(vector3(0, 0, 0), false);
		}
		else {
			// in the air, you can slightly nudge your character in a direction
			rigidBody->AddForce(dir * 5.f);
		}
		// face direction
		auto& thisTransform = GetOwner().GetTransform();
		auto rot = glm::quatLookAt(dir, thisTransform.WorldUp());
		rigidBody->setDynamicsWorldPose(thisTransform.GetWorldPosition(), Slerp(thisTransform.GetWorldRotation(), rot, 0.2));
		//GetTransform().SetWorldRotation(Slerp(GetTransform().GetWorldRotation(), rot, 0.2));
	}
}

void CharacterScript::Jump() {
	if (controlsEnabled) {
		if (OnGround()) {
			auto vel = rigidBody->GetLinearVelocity();
			vel.y = 10;
			rigidBody->SetLinearVelocity(vel, false);
		}
	}
}

void CharacterScript::Pound() {
	// we can pound if we are jumping or falling
	switch (animator->GetCurrentState()) {
		case CharAnims::Fall:
		case CharAnims::Jump:
			animator->Goto(CharAnims::PoundBegin);
			rigidBody->ClearAllForces();
			rigidBody->SetLinearVelocity(vector3(0,0,0), false);
			break;
		default:
			break;
	}
}

void CharacterScript::OnColliderEnter(PhysicsBodyComponent& other, const ContactPairPoint* contactPoints, size_t numContactPoints)
{
	if (other.filterGroup & FilterLayers::L0) {	// we use filter layer 0 to mark ground
		auto worldpos = GetOwner().GetTransform().GetWorldPosition();
		// is this contact point underneath the character?
		for (int i = 0; i < numContactPoints; i++) {
			auto diff = worldpos.y - contactPoints[i].position.y;
			if (diff > -0.3) {
				groundCounter++;
				break;
			}
		}

	}
}

void CharacterScript::OnColliderExit(PhysicsBodyComponent& other, const ContactPairPoint* contactPoints, size_t numContactPoints)
{
	if (other.filterGroup & FilterLayers::L0) {
		groundCounter--;
	}
}

void CharacterScript::StartPounding() {
	rigidBody->SetGravityEnabled(true);
	rigidBody->SetLinearVelocity(vector3(0,-5,0),false);
}


void Character::Create(Ref<MeshAssetSkinned> mesh, Ref<PBRMaterialInstance> material, Ref<SkeletonAsset> skeleton) {
    GameObject::Create();
	// setup animation
	// note: if you are loading multiple instances
	// of an animated character, you will want to load and store
	// the assets separately to avoid unnecessary disk i/o and parsing.
	auto all_clips = RavEngine::New<AnimationAsset>("character_anims.fbx", skeleton);
	auto walk_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 0, 47);
	auto idle_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 60,120);
	auto run_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 131, 149);
	auto jump_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 160, 163);
	auto fall_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 171, 177);
	auto pound_begin_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 180, 195);
	auto pound_do_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 196, 200);
	auto pound_end_anim = RavEngine::New<AnimationAssetSegment>(all_clips, 201, 207);

#if TRANSFORM_DEBUG
	auto childChildForTesting = GetWorld()->Instantiate<GameObject>();
	{
		auto testMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		testMat->SetAlbedoColor({0,1,0,1});
		auto mesh = MeshAsset::Manager::Get("cube.obj");
		childChildForTesting.EmplaceComponent<StaticMesh>(mesh,LitMeshMaterialInstance(testMat));

		EmplaceComponent<StaticMesh>(mesh, LitMeshMaterialInstance(testMat));	// also putting a mesh on the base object for testing transforms
	}
#endif

	auto childEntity = GetWorld()->Instantiate<GameObject>();										// I made the animation facing the wrong way
	GetTransform().AddChild(childEntity);								// so I need a child entity to rotate it back
	childEntity.GetTransform().LocalRotateDelta(vector3(0, deg_to_rad(180), 0));	// if your animations are the correct orientation you don't need this

#if TRANSFORM_DEBUG
    childEntity.GetTransform().AddChild(childChildForTesting);
	childChildForTesting.GetTransform().SetLocalPosition(vector3(0,5,0));
#endif

	// load the mesh and material onto the character
	auto& cubemesh = childEntity.EmplaceComponent<SkinnedMeshComponent>(skeleton, mesh);
	cubemesh.SetMaterial(LitMeshMaterialInstance(material));

	// load the collider and physics settings
    auto& r = EmplaceComponent<RigidBodyDynamicComponent>(FilterLayers::L0, FilterLayers::L0 | FilterLayers::L1);
    rigidBody = ComponentHandle<RigidBodyDynamicComponent>(this);
	r.EmplaceCollider<CapsuleCollider>(0.6f, 1.3f, RavEngine::New<PhysicsMaterial>(0.0f, 0.5f, 0.0f),vector3(0,1.7,0),vector3(0,0,deg_to_rad(90)));
	r.SetAxisLock(RigidBodyDynamicComponent::AxisLock::Angular_X | RigidBodyDynamicComponent::AxisLock::Angular_Z);
	r.SetWantsContactData(true);

	// load the animation
	auto& animcomp = childEntity.EmplaceComponent<AnimatorComponent>(skeleton);

	// the Sockets feature allows you to expose transforms at bones on an animated skeleton as though they were their own entities.
	// this is useful for attaching an object to a character's hand, as shown below.
	auto handEntity = GetWorld()->Instantiate<GameObject>();
    MeshAssetOptions opt;
    opt.scale = 0.4f;
	handEntity.EmplaceComponent<StaticMesh>(MeshAsset::Manager::Get("cone.obj", opt), LitMeshMaterialInstance(RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>())));
	
	childEntity.EmplaceComponent<ConstraintTarget>();
	// you must use the name from the importer. To see imported names, have your debugger print animcomp->skeleton->skeleton->joint_names_.data_+n
	auto handProxyEntity = GetWorld()->Instantiate<GameObject>();
	handProxyEntity.EmplaceComponent<SocketConstraint>(childEntity,"character:hand_r");
	handProxyEntity.GetTransform().AddChild(handEntity);
   
	// add an offset for the hand entity
	handEntity.GetTransform().LocalTranslateDelta(vector3(0,-0.5,0));
	
	// create the animation state machine
	AnimatorComponent::State
		idle_state{ CharAnims::Idle, idle_anim },
		walk_state{ CharAnims::Walk, walk_anim },
		run_state{ CharAnims::Run, run_anim },
		fall_state{ CharAnims::Fall, fall_anim },
		jump_state{ CharAnims::Jump, jump_anim },
		pound_begin_state{ CharAnims::PoundBegin, pound_begin_anim },
		pound_do_state{ CharAnims::InPound, pound_do_anim },
		pound_end_state{ CharAnims::PoundEnd, pound_end_anim };
	// some states should not loop
	jump_state.isLooping = false;
	fall_state.isLooping = false;
	pound_begin_state.isLooping = false;
	pound_end_state.isLooping = false;
	pound_do_state.isLooping = false;
	
	// adjust the speed of clips
	walk_state.speed = 2.0;

	// create transitions
	// if a transition between A -> B does not exist, the animation will switch instantly.
	idle_state.SetTransition(CharAnims::Walk, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Fall, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Jump, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Run, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	walk_state.SetTransition(CharAnims::Idle, TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Run, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended)
		.SetTransition(CharAnims::Fall, TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Jump, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	
	run_state.SetTransition(CharAnims::Walk, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::Blended)
		.SetTransition(CharAnims::Fall, TweenCurves::LinearCurve, 0.5, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Jump, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Idle, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	jump_state.SetTransition(CharAnims::Fall, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Walk, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Run, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Idle, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::PoundBegin, TweenCurves::LinearCurve, 0.1, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		;


	pound_begin_state.SetTransition(CharAnims::InPound, TweenCurves::LinearCurve, 0.1, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	pound_begin_state.SetAutoTransition(CharAnims::InPound);
	pound_do_state.SetTransition(CharAnims::PoundEnd, TweenCurves::LinearCurve, 0.1, AnimatorComponent::State::Transition::TimeMode::BeginNew);

	pound_end_state.SetAutoTransition(CharAnims::Idle);
	pound_end_state.SetTransition(CharAnims::Idle, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew);
	
	fall_state.SetTransition(CharAnims::Idle, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Walk, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Run, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::Jump, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		.SetTransition(CharAnims::PoundBegin, TweenCurves::LinearCurve, 0.2, AnimatorComponent::State::Transition::TimeMode::BeginNew)
		;

	// this script controls the animation
	EmplaceComponent<CharacterScript>(ComponentHandle<AnimatorComponent>(childEntity), ComponentHandle<RigidBodyDynamicComponent>(this));
    script = ComponentHandle<CharacterScript>(this);
    auto sccpy = script;
    auto callbacks = RavEngine::New<PhysicsCallback>();
    callbacks->OnColliderEnter = [sccpy](PhysicsBodyComponent& other, const ContactPairPoint* contactPoints, size_t numContactPoints) mutable{
        sccpy->OnColliderEnter(other, contactPoints, numContactPoints);
    };
    callbacks->OnColliderExit = [sccpy](PhysicsBodyComponent& other, const ContactPairPoint* contactPoints, size_t numContactPoints) mutable{
        sccpy->OnColliderExit(other, contactPoints, numContactPoints);
    };
    
	rigidBody->AddReceiver(callbacks);

	pound_begin_state.SetBeginCallback([sccpy](uint16_t nextState) mutable {
		sccpy->rigidBody->SetGravityEnabled(false);
		sccpy->controlsEnabled = false;
	});
	pound_do_state.SetBeginCallback([sccpy] (uint16_t nextState) mutable {
		sccpy->StartPounding();
	});
	pound_end_state.SetEndCallback([sccpy] (uint16_t nextState) mutable {
		sccpy->controlsEnabled = true;
	});

	// add transitions to the animator component
	// note that these are copied into the component, so making changes
	// to states after insertion will not work!
	animcomp.InsertState(walk_state);
	animcomp.InsertState(idle_state);
	animcomp.InsertState(run_state);
	animcomp.InsertState(jump_state);
	animcomp.InsertState(fall_state);
	animcomp.InsertState(pound_begin_state);
	animcomp.InsertState(pound_end_state);
	animcomp.InsertState(pound_do_state);

	// initialize the state machine
	// if an entry state is not set before play, your game will crash.
	animcomp.Goto(CharAnims::Idle, true);

	// begin playing the animator controller.
	// animator controllers are asynchronous to your other code
	// so play and pause simply signal the controller to perform an action
	animcomp.Play();
    animcomp.debugEnabled = true;
}

void Character::Move(const vector3& dir, decimalType speedMultiplier){
	script->Move(dir, speedMultiplier);
}

void Character::Jump()
{
	script->Jump();
}
void Character::Pound() {
	script->Pound();
}

void CharacterScriptRunner::operator()(CharacterScript& script) 
{
	const auto fpsScale = GetApp()->GetCurrentFPSScale();
	script.Tick(fpsScale);
}
