#pragma once
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <string>
#include <vector>

#include "rapidjson\document.h"

#include "Geometry.h"
#include "Unit.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

namespace ConquestOfCastles {

	class GoldMine {
	private:
		Vector2D pos;
		int goldAmount;

	public:
		Vector2D Pos();
		int GoldAmount();

		GoldMine(Vector2D& pos, int goldAmount);
		GoldMine(Value& data);
	};

}

#endif