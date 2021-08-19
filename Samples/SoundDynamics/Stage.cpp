#include "Speaker.hpp"
#include <RavEngine/AudioRoom.hpp>

using namespace std;
using namespace RavEngine;

Stage::Stage() {
	auto audioRoom = EmplaceComponent<AudioRoom>();
	audioRoom->SetRoomDimensions(vector3(5, 30, 5));

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
	EmplaceComponent<RoomDebugRenderer>();
}