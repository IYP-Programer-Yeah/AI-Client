#pragma once

#include "ClientManager.h"
#include <iostream>
#include <time.h>

#define min(a,b) a>b?b:a
#define max(a,b) a<b?b:a
#define clamp(x,a,b) min(max(a,x),b)

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
		if (x != clamp(x, 0, width - 1) || y != clamp(y, 0, height - 1))
			return true;
		return world[x + y*width].Blocked;
	}
	tile* get_tile(int x, int y)
	{
		x = clamp(x, 0, width - 1);
		y = clamp(y, 0, height - 1);
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