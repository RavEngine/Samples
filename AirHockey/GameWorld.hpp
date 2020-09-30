#include <RavEngine/World.hpp>
#include "Puck.hpp"
#include "Table.hpp"

using namespace RavEngine;

class GameWorld : public RavEngine::World {
public:
	GameWorld();

	void posttick(float) override;
    
    Ref<Table> hockeytable = new Table();
    Ref<Puck> puck = new Puck();
};
