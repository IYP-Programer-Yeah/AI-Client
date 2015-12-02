#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Geometry.h"
#include "Unit.h"

using namespace std;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {

	class Player {
	public:
		int Gold();
		int Id();
		string Name();
		vector<Unit*> Agents();
	};

}

#endif