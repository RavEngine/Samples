#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include "Table.hpp"
#include "Paddle.hpp"
#include "Player.hpp"

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld();

	void posttick(float) override;
    
protected:
    Ref<Table> hockeytable = new Table();
    Ref<Puck> puck = new Puck();
	
	Ref<Entity> cameraBoom = new Entity();
	
	Ref<Paddle> p1;
	Ref<Paddle> p2;

	int p1score = 0, p2score = 0, numToWin = 3;
	
	void Reset();
};
