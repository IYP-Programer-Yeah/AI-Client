#pragma once
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <string>
#include <vector>

#include "Geometry.h"
#include "Unit.h"

using namespace std;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {

	class GoldMine {
	public:
		Vector2D Pos();
		int GoldAmount();
	};

}

#endif