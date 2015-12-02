#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "UnitType.h"
#include "Commands.h"

using namespace std;
using namespace ConquestOfCastles;

namespace ConquestOfCastles {

	class Unit{
	private:
		UnitType type;
		int id;
		int owner;
		int HP;
		int ATK;
		Vector2D pos;
		Command* cmd;
	public:
		UnitType Type();
		int Id();
		int Owner();
		int Hp();
		int Atk();
		Vector2D Pos();
		Command* Command();

		Unit(Value& data);
		~Unit();
		void Move(Direction dir);
		void Attack(Direction dir);
		void Make(Direction dir, UnitType type);


	public:
		static string Parse(UnitType type);
		static UnitType Parse(string type);
	};
}

#endif