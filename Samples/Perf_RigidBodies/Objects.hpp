#pragma once
#include <RavEngine/GameObject.hpp>

namespace RavEngine {
	class MeshAsset;
	class PBRMaterialInstance;
	class PhysicsMaterial;
	struct MeshCollectionStatic;
}

struct RotationComponent : public RavEngine::AutoCTTI{
	float xspeed = 0.5, yspeed = 0.2, zspeed = 0.4, maxDeg = 10;
};

struct Ground : public RavEngine::GameObject{
	void Create();
};

struct RigidBody : public RavEngine::GameObject{
	enum class BodyType{
		Sphere,
		Cube
	};
	
	void Create(Ref<RavEngine::PBRMaterialInstance> mat, Ref<RavEngine::MeshCollectionStatic> mesh, Ref<RavEngine::PhysicsMaterial> physmat, BodyType type);
};
