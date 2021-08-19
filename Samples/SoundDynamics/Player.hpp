#include <RavEngine/Entity.hpp>

struct PlayerController;
struct Player : public RavEngine::Entity {

	Player();
	void MoveForward(float);
	void MoveRight(float);
	void MoveUp(float);

	void LookRight(float);
	void LookUp(float);

	Ref<PlayerController> GetScript();

};