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
		vector <GoldMine*> Mines = world->GoldMines();
		if (First_Run)
		{
			std::cout << Map.width << "  " << Map.height << endl;
			temp_tile = Map.get_tile(Self->Agents()[0]->Pos().X(), Self->Agents()[0]->Pos().Y());
			temp_tile->Blocked = true;
			temp_tile->Terrain = Tile_Castle;
			First_Run = false;
		}
		if (units.size() < 4 || units.size() <= Mines.size())
			Castle->Make(Direction::EAST, UnitType::WORKER);
		bool *WorkerOnGold = new bool[units.size()];
		for (int i = 1; i < units.size(); i++)
		{
			WorkerOnGold[i] = false;
			for (int j = 0; j < Mines.size(); j++)
				if (units[i]->Pos() == Mines[j]->Pos() && Mines[j]->GoldAmount() != 0)
				{
					WorkerOnGold[i] = true;
					break;
				}
			if (!WorkerOnGold[i])
			{
				srand((int)time(0));
				float chance = (rand() % 4) / 4.0;

				if (chance < 0.25)
					units[i]->Move(Direction::NORTH);
				else if (chance < 0.5)
					units[i]->Move(Direction::SOUTH);
				else if (chance < 0.75)
					units[i]->Move(Direction::EAST);
				else
					units[i]->Move(Direction::WEST);
			}

		}

	}

}