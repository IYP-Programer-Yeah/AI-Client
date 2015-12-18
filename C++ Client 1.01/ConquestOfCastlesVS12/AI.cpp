#include "AI.h"


vector<Direction> BFS(map* Map, Vector2D start, Vector2D end)
{
	int Sx = start.X(), Sy = start.Y();
	int Ex = end.X(), Ey = end.Y();

	vector<int>Xs;
	vector<int>Ys;

	Xs.push_back(Ex);
	Ys.push_back(Ey);

	bool *Done = new bool[Map->width*Map->height];
	for (int i = 0; i < Map->width*Map->height; i++)
		Done[i] = false;

	Vector2D temp(-1, -1);

	while (Xs.size())
	{
		if (!Map->is_blocked(Xs[0] + 1, Ys[0]) && !Done[Xs[0] + Ys[0] * Map->width])
		{
			Xs.push_back(Xs[0] + 1);
			Ys.push_back(Ys[0]);
			Done[Xs[Xs.size() - 1] + Ys[Xs.size() - 1] * Map->width] = true;
			if (Xs[Xs.size() - 1] == Sx)
				if (Ys[Ys.size() - 1] == Sy)
				{
					temp = Vector2D(Xs[0], Ys[0]);
					break;
				}
		}
		if (!Map->is_blocked(Xs[0] - 1, Ys[0]) && !Done[Xs[0] + Ys[0] * Map->width])
		{
			Xs.push_back(Xs[0] - 1);
			Ys.push_back(Ys[0]);
			if (Xs[Xs.size() - 1] == Sx)
				if (Ys[Ys.size() - 1] == Sy)
				{
					temp = Vector2D(Xs[0], Ys[0]);
					break;
				}
		}
		if (!Map->is_blocked(Xs[0], Ys[0] + 1) && !Done[Xs[0] + Ys[0] * Map->width])
		{
			Xs.push_back(Xs[0]);
			Ys.push_back(Ys[0] + 1);
			if (Xs[Xs.size() - 1] == Sx)
				if (Ys[Ys.size() - 1] == Sy)
				{
					temp = Vector2D(Xs[0], Ys[0]);
					break;
				}
		}
		if (!Map->is_blocked(Xs[0], Ys[0] - 1) && !Done[Xs[0] + Ys[0] * Map->width])
		{
			Xs.push_back(Xs[0]);
			Ys.push_back(Ys[0] - 1);
			if (Xs[Xs.size() - 1] == Sx)
				if (Ys[Ys.size() - 1] == Sy)
				{
					temp = Vector2D(Xs[0], Ys[0]);
					break;
				}
		}
		delete Done;
		Xs.erase(Xs.begin());
		Ys.erase(Ys.begin());
	}
	vector<Direction> ret;
	if (start[Direction::NORTH] == temp)
		ret.push_back(Direction::NORTH);
	if (start[Direction::SOUTH] == temp)
		ret.push_back(Direction::SOUTH);
	if (start[Direction::EAST] == temp)
		ret.push_back(Direction::EAST);
	if (start[Direction::WEST] == temp)
		ret.push_back(Direction::WEST);
	return ret;
}

Direction FindDir(map* Map, Vector2D start, Vector2D end)
{

	Direction MoveMent;
	int MinDist = (abs((end - start).X()) + 1)*(abs((end - start).X()) + 1) + (abs((end - start).Y()) + 1)*(abs((end - start).Y()) + 1);

	int TempInt;

	Vector2D temp = end - start;

	if (!Map->is_blocked(start[Direction::NORTH].X(), start[Direction::NORTH].Y()))
	{
		TempInt = temp[Direction::SOUTH].X()*temp[Direction::SOUTH].X() + temp[Direction::SOUTH].Y()*temp[Direction::SOUTH].Y();
		if (TempInt < MinDist)
		{
			MinDist = TempInt;
			MoveMent = Direction::NORTH;
		}
	}
	if (!Map->is_blocked(start[Direction::SOUTH].X(), start[Direction::SOUTH].Y()))
	{
		TempInt = temp[Direction::NORTH].X()*temp[Direction::NORTH].X() + temp[Direction::NORTH].Y()*temp[Direction::NORTH].Y();
		if (TempInt < MinDist)
		{
			MinDist = TempInt;
			MoveMent = Direction::SOUTH;
		}
	}
	if (!Map->is_blocked(start[Direction::EAST].X(), start[Direction::EAST].Y()))
	{
		TempInt = temp[Direction::WEST].X()*temp[Direction::WEST].X() + temp[Direction::WEST].Y()*temp[Direction::WEST].Y();
		if (TempInt < MinDist)
		{
			MinDist = TempInt;
			MoveMent = Direction::EAST;
		}
	}
	if (!Map->is_blocked(start[Direction::WEST].X(), start[Direction::WEST].Y()))
	{
		TempInt = temp[Direction::EAST].X()*temp[Direction::EAST].X() + temp[Direction::EAST].Y()*temp[Direction::EAST].Y();
		if (TempInt < MinDist)
		{
			MinDist = TempInt;
			MoveMent = Direction::WEST;
		}
	}
	return MoveMent;
}


namespace ConquestOfCastles{
	void PlayerAI::DoTurn(WorldModel* world)
	{
		static bool First_Run = true;
		static map Map(world->Terrain());
		static vector<UnitAI> UinitAIs;
		static Direction FreePos;
		static vector<UnitAI> EnemyUinitAIs;

		Player *Self = world->Self();
		std::cout << "Team: " << Self->Name() << " Gold: " << Self->Gold() << endl;
		vector<Unit*> units = Self->Agents();
		vector<Unit*> enemyUnits = world->Players()[0]->Agents();

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
			if (Map.is_blocked(Castle->Pos()[Direction::NORTH].X(), Castle->Pos()[Direction::NORTH].Y()))
				FreePos = Direction::NORTH;
			if (Map.is_blocked(Castle->Pos()[Direction::SOUTH].X(), Castle->Pos()[Direction::NORTH].Y()))
				FreePos = Direction::SOUTH;
			if (Map.is_blocked(Castle->Pos()[Direction::EAST].X(), Castle->Pos()[Direction::NORTH].Y()))
				FreePos = Direction::EAST;
			if (Map.is_blocked(Castle->Pos()[Direction::WEST].X(), Castle->Pos()[Direction::NORTH].Y()))
				FreePos = Direction::WEST;
		}

		for (int i = 1; i < units.size(); i++)
			if (UinitAIs.size() == 0 || UinitAIs[UinitAIs.size() - 1].ID < units[i]->Id())
			{
				UnitAI temp(&Map);
				temp.ID = units[i]->Id();
				UinitAIs.push_back(temp);
			}

		for (int i = 0; i < UinitAIs.size(); i++)
		{
			UinitAIs[i].GetUnitPtr(&units);
			UinitAIs[i].CheckOnGold(&Mines);
		}

		/*for (int i = 0; i < enemyUnits.size(); i++)
			if (EnemyUinitAIs.size() == 0 || EnemyUinitAIs[EnemyUinitAIs.size() - 1].ID < enemyUnits[i]->Id())
			{
				UnitAI temp(&Map);
				temp.ID = enemyUnits[i]->Id();
				EnemyUinitAIs.push_back(temp);
			}

		for (int i = 0; i < EnemyUinitAIs.size(); i++)
		{
			EnemyUinitAIs[i].GetUnitPtr(&units);
			EnemyUinitAIs[i].CheckOnGold(&Mines);
		}*/

		//Map.CheckUnits(&UnitAIs);
		if (units.size() % 2 == 0)
		{
			if (units.size()/2 < 10 || units.size()/2 <= Mines.size())
				Castle->Make(FreePos, UnitType::WORKER);
		}
		else
		{
			Castle->Make(FreePos, UnitType::WARRIOR);
		}



		for (int i = 0; i < UinitAIs.size(); i++)
		{
			if (UinitAIs[i].UnitPtr->Type() == UnitType::WARRIOR)
			{
				bool tempB = false;
				for (int i = 0; i < enemyUnits.size(); i++)
				{
					if (UinitAIs[i].UnitPtr->Pos()[Direction::NORTH] == enemyUnits[i]->Pos())
					{
						UinitAIs[i].UnitPtr->Attack(Direction::NORTH);
						tempB = true;
					}
					else if (UinitAIs[i].UnitPtr->Pos()[Direction::SOUTH] == enemyUnits[i]->Pos())
					{
						UinitAIs[i].UnitPtr->Attack(Direction::SOUTH);
						tempB = true;
					}
					else if (UinitAIs[i].UnitPtr->Pos()[Direction::EAST] == enemyUnits[i]->Pos())
					{
						UinitAIs[i].UnitPtr->Attack(Direction::EAST);
						tempB = true;
					}
					else if (UinitAIs[i].UnitPtr->Pos()[Direction::WEST] == enemyUnits[i]->Pos())
					{
						UinitAIs[i].UnitPtr->Attack(Direction::WEST);
						tempB = true;
					}
				}
				if (!tempB)
					UinitAIs[i].move(FindDir(&Map, UinitAIs[i].UnitPtr->Pos(), enemyUnits[0]->Pos()));
			}
			else
			{
				Vector2D temp = UinitAIs[i].FindNearest();
				int Nx = temp.X(), Ny = temp.Y();
				if (!UinitAIs[i].OnGold)
				{
					//vector<Direction> Dir = BFS(&Map, UinitAIs[i].UnitPtr->Pos(), /*temp*/UinitAIs[i].UnitPtr->Pos() - Vector2D(2, 2));

					UinitAIs[i].move(FindDir(&Map, UinitAIs[i].UnitPtr->Pos(), temp));
				}
			}
		}

	}

}