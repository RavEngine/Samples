#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include "Table.hpp"
#include "Paddle.hpp"
#include "Player.hpp"
#include <RavEngine/GUI.hpp>

namespace RavEngine{
	class AudioAsset;
}

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld(int numplayers, Ref<RavEngine::AudioAsset>);
	
	GameWorld(const GameWorld& other);
	
	void PostTick(float) override;
	
    
protected:
    GameObject hockeytable = Instantiate<Table>();
    GameObject puck = Instantiate<Puck>();
	
	GameObject cameraBoom = Instantiate<GameObject>();
	
	Paddle p1;
	Paddle p2;

	int numplayers;
	
	int p1score = 0, p2score = 0, numToWin = 3;
	
	Rml::Element* Scoreboard = nullptr;
	Ref<RavEngine::AudioAsset> musicAsset;
	
	void Reset();
	void GameOver();
};
