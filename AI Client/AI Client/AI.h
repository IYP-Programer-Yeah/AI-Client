#pragma once

#include "ClientManager.h"
#include <iostream>

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