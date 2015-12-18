#include "PlayerAI.h"
#include "GameObjects.h"
#include "Geometry.h"
#include "Player.h"
#include "Unit.h"
#include "UnitType.h"
#include "WorldModel.h"


using namespace std;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {
	
	void PlayerAI::DoTurn(WorldModel* world) {
		Random random;

		Unit* castle = world->Self()->Agents().at(0);
		int number_of_agents = world->Self()->Agents().size();
		
		for (int i = 1; i < number_of_agents; i++) {
			Unit* mc = world->Self()->Agents().at(i);

			float chance = random.next_double();

			if (chance < 0.25)
				mc->Move(Direction::NORTH);
			else if (chance < 0.5)
				mc->Move(Direction::SOUTH);
			else if (chance < 0.75)
				mc->Move(Direction::EAST);
			else
				mc->Move(Direction::WEST);
		}

		float r = random.next_double();
		if (r > 0.5)
			castle->Make(Direction::EAST, UnitType::WORKER);
		else
			castle->Make(Direction::WEST, UnitType::WORKER);

	}
}