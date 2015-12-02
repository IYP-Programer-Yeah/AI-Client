#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "rapidjson\document.h"

#include "Geometry.h"
#include "Unit.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

namespace ConquestOfCastles {

	class Player {
	private:
		int gold;
		int id;
		string name;
		vector<Unit*> agents;
	public:
		int Gold();
		int Id();
		string Name();
		vector<Unit*> Agents();

		Player();
		Player(Value& data);
		~Player();
	};

}

#endif