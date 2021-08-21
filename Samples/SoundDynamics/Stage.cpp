#include "Speaker.hpp"
#include <RavEngine/AudioRoom.hpp>
#include <RavEngine/ChildEntityComponent.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/SceneLoader.hpp>

using namespace std;
using namespace RavEngine;

Stage::Stage() {
	auto roomEntity = make_shared<Entity>();

	auto audioRoom = roomEntity->EmplaceComponent<AudioRoom>();
	audioRoom->SetRoomDimensions(vector3(20, 10, 20));

	EmplaceComponent<ChildEntityComponent>(roomEntity);
	GetTransform()->AddChild(roomEntity->GetTransform());

	// load room
	SceneLoader loader("room.fbx");
	loader.LoadMeshes([&](const PreloadedAsset& pr) -> bool {
		// we want to load all meshes in this case
		return true;

	}, [&](Ref<MeshAsset> rm, const PreloadedAsset& pr) {
		EmplaceComponent<StaticMesh>(rm, make_shared<PBRMaterialInstance>(Material::Manager::AccessMaterialOfType<PBRMaterial>()));
	});
	GetTransform()->LocalTranslateDelta(vector3(0,audioRoom->GetRoomDimensions().y / 2,0));

	struct RoomDebugRenderer : public IDebugRenderer {
		void DrawDebug(RavEngine::DebugDraw& dbg) const override {
			auto owner = std::static_pointer_cast<Entity>(GetOwner().lock());
			if (owner) {
				auto room = owner->GetComponent<AudioRoom>();
				if (room) {
					room.value()->DrawDebug(dbg);
				}
			}
		}
	};
	roomEntity->EmplaceComponent<RoomDebugRenderer>();
}

Ref<AudioRoom> Stage::GetRoom()
{
	return GetComponent<ChildEntityComponent>().value()->GetEntity()->GetComponent<AudioRoom>().value();
}
