#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "rapidjson\document.h"
#include "Serializable.h"

using namespace ConquestOfCastles;
using namespace rapidjson;
using namespace std;

namespace ConquestOfCastles {

	enum Direction {
		NORTH,
		WEST,
		SOUTH,
		EAST
	};

	class Vector2D : public Serializable {
	private:
		int x;
		int y;
	public:
		int X();
		int Y();

		void Serialize(Writer<StringBuffer>& writer);

		Vector2D(Value& data);
		Vector2D();
		Vector2D(int x, int y);
		Vector2D operator + (Vector2D& vector2d);
		Vector2D operator - (Vector2D& vector2d);
		Vector2D operator += (Vector2D& vector2d);
		Vector2D operator -= (Vector2D& vector2d);
		bool operator == (Vector2D& vector2d);
		double Length();
		double Distance(Vector2D vector2d);
		Vector2D operator[] (Direction direction);
	};
}

#endif