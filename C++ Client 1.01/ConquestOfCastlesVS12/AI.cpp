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
		int *WorkersNearestNode = new int[units.size() * 2];
		srand((int)time(0));
		for (int i = 1; i < units.size(); i++)
		{
			WorkerOnGold[i] = false;
			for (int j = 0; j < Mines.size(); j++)
				if (units[i]->Pos() == Mines[j]->Pos() && Mines[j]->GoldAmount() != 0)
				{
					WorkerOnGold[i] = true;
					WorkersNearestNode[i * 2] = 0;
					WorkersNearestNode[i * 2 + 1] = 0;
					break;
				}
			if (!WorkerOnGold[i])
			{
				WorkersNearestNode[i * 2] = max(Map.width - units[i]->Pos().X(), units[i]->Pos().X() + 1);
				WorkersNearestNode[i * 2 + 1] = max(Map.height - units[i]->Pos().Y(), units[i]->Pos().Y() + 1);
				int dis2 = WorkersNearestNode[i * 2] * WorkersNearestNode[i * 2] + WorkersNearestNode[i * 2 + 1] * WorkersNearestNode[i * 2 + 1];

				int UnitX = units[i]->Pos().X(), UnitY = units[i]->Pos().Y();

				for (int j = 0; j < WorkersNearestNode[i * 2] && j*j < dis2; j++)
					for (int k = 0; k < WorkersNearestNode[i * 2 + 1] && dis2 > k*k + j*j; k++)
					{
						if (Map.get_tile(UnitX + j, UnitY + k)->Terrain == -1 && !Map.is_blocked(UnitX + j, UnitY + k))
						{
							WorkersNearestNode[i * 2] = j;
							WorkersNearestNode[i * 2 + 1] = k;
							int dis2 = WorkersNearestNode[i * 2] * WorkersNearestNode[i * 2] + WorkersNearestNode[i * 2 + 1] * WorkersNearestNode[i * 2 + 1];
							break;
						}
						if (Map.get_tile(UnitX - j, UnitY + k)->Terrain == -1 && !Map.is_blocked(UnitX - j, UnitY + k))
						{
							WorkersNearestNode[i * 2] = -j;
							WorkersNearestNode[i * 2 + 1] = k;
							int dis2 = WorkersNearestNode[i * 2] * WorkersNearestNode[i * 2] + WorkersNearestNode[i * 2 + 1] * WorkersNearestNode[i * 2 + 1];
							break;
						}
						if (Map.get_tile(UnitX + j, UnitY - k)->Terrain == -1 && !Map.is_blocked(UnitX + j, UnitY - k))
						{
							WorkersNearestNode[i * 2] = j;
							WorkersNearestNode[i * 2 + 1] = -k;
							int dis2 = WorkersNearestNode[i * 2] * WorkersNearestNode[i * 2] + WorkersNearestNode[i * 2 + 1] * WorkersNearestNode[i * 2 + 1];
							break;
						}
						if (Map.get_tile(UnitX - j, UnitY - k)->Terrain == -1 && !Map.is_blocked(UnitX - j, UnitY - k))
						{
							WorkersNearestNode[i * 2] = -j;
							WorkersNearestNode[i * 2 + 1] = -k;
							int dis2 = WorkersNearestNode[i * 2] * WorkersNearestNode[i * 2] + WorkersNearestNode[i * 2 + 1] * WorkersNearestNode[i * 2 + 1];
							break;
						}
					}

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
		srand((int)time(0));

	}

}