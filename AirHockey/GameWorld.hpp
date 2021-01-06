#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include "Table.hpp"
#include "Paddle.hpp"
#include "Player.hpp"
#include <RavEngine/GUI.hpp>

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld(bool multiplayer);
	
	GameWorld(const GameWorld& other);

	void posttick(float) override;
	
    
protected:
    Ref<Table> hockeytable = new Table();
    Ref<Puck> puck = new Puck();
	
	Ref<Entity> cameraBoom = new Entity();
	
	Ref<Paddle> p1;
	Ref<Paddle> p2;

	bool isMultiplayer;
	
	int p1score = 0, p2score = 0, numToWin = 3;
	
	Rml::Element* Scoreboard = nullptr;
	
	void Reset();
	void GameOver();
};
