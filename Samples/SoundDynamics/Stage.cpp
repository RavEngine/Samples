#include "Speaker.hpp"
#include <RavEngine/AudioRoom.hpp>
#include <RavEngine/ChildEntityComponent.hpp>

using namespace std;
using namespace RavEngine;

Stage::Stage() {
	auto roomEntity = make_shared<Entity>();

	auto audioRoom = roomEntity->EmplaceComponent<AudioRoom>();
	audioRoom->SetRoomDimensions(vector3(30, 10, 30));
	roomEntity->GetTransform()->LocalTranslateDelta(vector3(0,audioRoom->GetRoomDimensions().y/2,0));

	EmplaceComponent<ChildEntityComponent>(roomEntity);
	GetTransform()->AddChild(roomEntity->GetTransform());

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