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
	public:
		UnitType Type();
		int Id();
		int Owner();
		int Hp();
		int Atk();
		Vector2D Pos();

		void Move(Direction dir);
		void Attack(Direction dir);
		void Make(Direction dir, UnitType type);
	};
}

#endif