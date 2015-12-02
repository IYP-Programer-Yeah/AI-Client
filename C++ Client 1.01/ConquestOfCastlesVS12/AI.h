#pragma once

#include "ClientManager.h"
#include <iostream>
#include <time.h>

#define min(a,b) a>b?b:a

class tile
{
public:
	bool Blocked;
	int Terrain;
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
		return world[x + y*width].Blocked;
	}
	tile* get_tile(int x, int y)
	{
		return &world[x + y*width];
	}
};

namespace ConquestOfCastles{
	class PlayerAI : public IPlayerAI
	{
	public:
		void DoTurn(WorldModel* world);
	};
}