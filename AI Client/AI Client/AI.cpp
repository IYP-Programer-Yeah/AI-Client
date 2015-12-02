#include "AI.h"

#define Tile_Castle 10
/*#define Castle 10
#define Castle 10*/


namespace ConquestOfCastles{
	void PlayerAI::DoTurn(WorldModel* world)
	{
		static bool First_Run = true;
		static map Map(world->Terrain());
		Player *Self = world->Self();
		std::cout << "Team: " << Self->Name() << " Gold: " << Self->Gold() << endl;
		vector<Unit*> units = Self->Agents();
		Unit* Castle = units[0];
		tile *temp_tile;
		if (First_Run)
		{
			std::cout << Map.width << "  " << Map.height << endl;
			temp_tile = Map.get_tile(Castle->Pos().X(), Castle->Pos().Y());
			temp_tile->Blocked = true;
			temp_tile->Terrain = Tile_Castle;
			First_Run = false;
		}
	}

}