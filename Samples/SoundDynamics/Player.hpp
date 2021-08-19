#include <RavEngine/Entity.hpp>

struct Player : public RavEngine::Entity {

	Player();
	void MoveForward(float);
	void MoveRight(float);

	void MoveUp(float);

};