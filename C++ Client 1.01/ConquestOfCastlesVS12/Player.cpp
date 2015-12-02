#pragma once
#include <string>
#include <vector>

#include "rapidjson\document.h"

#include "Geometry.h"
#include "Unit.h"
#include "GameObjects.h"
#include "Player.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

namespace ConquestOfCastles {

	int Player::Gold() { return gold; }
	int Player::Id() { return id; }
	string Player::Name() { return name; }
	vector<Unit*> Player::Agents() { return agents; }

	Player::Player() : id(0), name("") {}

	Player::Player(Value & data)
	{
		gold = data["gold"].GetInt();
		id = data["PlayerId"].GetInt();
		name = data["name"].GetString();

		//updating agents
		int agentsCount = data["Agents"][0][0].Size();
		for (int i = 0; i < agentsCount; i++)
			agents.push_back(new Unit(data["Agents"][0][0][i]));
	}

	Player::~Player()
	{
		for (Unit* u : agents)
			delete u;
		agents.clear();
	}
}