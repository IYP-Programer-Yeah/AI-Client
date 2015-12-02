#pragma once
#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <vector>
#include <string>

#include "rapidjson\document.h"
#include "GameObjects.h"
#include "Player.h"

using namespace std;
using namespace rapidjson;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {
	
	class Terrain {
	private:
		int** terrain;
		int terrainWidth;
		int terrainHeight;

	public:
		Terrain() : terrain(nullptr) {}
		Terrain(Value& data);
		~Terrain();
		int Width();
		int Height();
		int Get(int x, int y);
	};

	class WorldModel {
	private:

		static Player* self;
		static Terrain* terrain;

		vector<GoldMine*> goldMines;
		vector<Player*> others;

	public:
		WorldModel(Value& data);
		WorldModel();
		~WorldModel();

		void SetSelf(Value& data);
		void SetTerrain(Value& data);
		void SetGoldMines(Value& data);

		Player* Self();
		Terrain* Terrain();
		vector<GoldMine*> GoldMines();
		vector<Player*> Players();
	};
}

#endif