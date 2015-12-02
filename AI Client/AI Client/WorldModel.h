#pragma once
#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <vector>
#include <string>

#include "GameObjects.h"
#include "Player.h"

using namespace std;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {
	
	class Terrain {
	public:
		int Width();
		int Height();
		int Get(int x, int y);
	};

	class WorldModel {
	public:
		Player* Self();
		Terrain* Terrain();
		vector<GoldMine*> GoldMines();
		vector<Player*> Players();
	};
}

#endif