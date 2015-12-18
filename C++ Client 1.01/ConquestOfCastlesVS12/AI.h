#pragma once

#include "ClientManager.h"
#include <iostream>
#include <time.h>

#define min(a,b) ((a>b)?b:a)
#define max(a,b) ((a<b)?b:a)
#define clamp(x,a,b) min(max(a,x),b)

#define Tile_Castle 11

class tile
{
public:
	bool Blocked;
	int Terrain;
	Unit* UnitPtr;
	tile()
	{
		Blocked = false;
		Terrain = -1;
	}
};

class map
{
public:

	tile* world;
	Terrain* terrain;
	int width;
	int height;
	map(Terrain* iterrain)
	{
		terrain = iterrain;
		width = terrain->Width();
		height = terrain->Height();
		world = new tile[width*height];
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				if (terrain->Get(i, j)>0)
					get_tile(i, j)->Blocked = true;
	}

	bool is_blocked(int x, int y)
	{
		if (x != clamp(x, 0, width - 1) || y != clamp(y, 0, height - 1))
			return true;
		return world[x + y*width].Blocked;
	}
	bool is_bloacked_dynamic(int x, int y)
	{
		return world[x + y*width].UnitPtr != NULL || is_blocked(x, y);
	}
	tile* get_tile(int x, int y)
	{
		x = clamp(x, 0, width - 1);
		y = clamp(y, 0, height - 1);
		return &world[x + y*width];
	}
	void set_tile_terrain(int x, int y, int terrain)
	{
		x = clamp(x, 0, width - 1);
		y = clamp(y, 0, height - 1);
		world[x + y*width].Terrain = terrain;
	}
};

class UnitAI
{
public:
	int ID;
	map* Map;
	int goal_x, goal_y;
	int task;
	Unit* UnitPtr;
	bool LastMoveWasDone;
	int x, y;
	Vector2D LastPos;
	bool OnGold;

	UnitAI(map* iMap)
	{
		Vector2D temp(-1, -1);
		LastPos = temp;
		Map = iMap;
	}
	void GetUnitPtr(vector<Unit*>* Units)
	{
		for (int i = 0; i < Units->size(); i++)
			if (Units->at(i)->Id()==ID)
				UnitPtr = Units->at(i);
		LastMoveWasDone = !(LastPos == UnitPtr->Pos());
		x = UnitPtr->Pos().X();
		y = UnitPtr->Pos().Y();
		if (Map->get_tile(x, y)->Terrain == -1)
			Map->set_tile_terrain(x, y, 0);
	}
	void move(Direction Dir)
	{
		LastPos = UnitPtr->Pos();
		UnitPtr->Move(Dir);
	}
	void CheckOnGold(vector<GoldMine*>* GoldMines)
	{
		for (int j = 0; j < GoldMines->size(); j++)
			if (UnitPtr->Pos() == GoldMines->at(j)->Pos() && GoldMines->at(j)->GoldAmount() != 0)
			{
				OnGold = true;
				return;
			}
		OnGold = false;
	}
	Vector2D FindNearest()
	{
		int WorkersNearestNode[2];
		WorkersNearestNode[0] = max(Map->width - x, x + 1);
		WorkersNearestNode[1] = max(Map->height - y, y + 1);
		int dis2 = WorkersNearestNode[0] * WorkersNearestNode[0] + WorkersNearestNode[1] * WorkersNearestNode[1];


		for (int j = 0; j < WorkersNearestNode[0] && j*j < dis2; j++)
			for (int k = 0; k < WorkersNearestNode[1] && dis2 > k*k + j*j; k++)
			{
				if (j*j + k*k < dis2)
				{
					if (Map->get_tile(x + j, y + k)->Terrain == -1 && !Map->is_blocked(x + j, y + k))
					{
						WorkersNearestNode[0] = j;
						WorkersNearestNode[1] = k;
						dis2 = WorkersNearestNode[0] * WorkersNearestNode[0] + WorkersNearestNode[1] * WorkersNearestNode[1];
						break;
					}
					if (Map->get_tile(x - j, y + k)->Terrain == -1 && !Map->is_blocked(x - j, y + k))
					{
						WorkersNearestNode[0] = -j;
						WorkersNearestNode[1] = k;
						dis2 = WorkersNearestNode[0] * WorkersNearestNode[0] + WorkersNearestNode[1] * WorkersNearestNode[1];
						break;
					}
					if (Map->get_tile(x + j, y - k)->Terrain == -1 && !Map->is_blocked(x + j, y - k))
					{
						WorkersNearestNode[0] = j;
						WorkersNearestNode[1] = -k;
						dis2 = WorkersNearestNode[0] * WorkersNearestNode[0] + WorkersNearestNode[1] * WorkersNearestNode[1];
						break;
					}
					if (Map->get_tile(x - j, y - k)->Terrain == -1 && !Map->is_blocked(x - j, y - k))
					{
						WorkersNearestNode[0] = -j;
						WorkersNearestNode[1] = -k;
						dis2 = WorkersNearestNode[0] * WorkersNearestNode[0] + WorkersNearestNode[1] * WorkersNearestNode[1];
						break;
					}
				}
			}
		Vector2D temp(WorkersNearestNode[0] + x, WorkersNearestNode[1] + y);
		return temp;
	}
};

namespace ConquestOfCastles{
	class PlayerAI : public IPlayerAI
	{
	public:
		void DoTurn(WorldModel* world);
	};
}