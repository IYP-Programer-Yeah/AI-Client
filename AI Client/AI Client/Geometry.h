#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

using namespace std;

namespace ConquestOfCastles {

	enum Direction {
		NORTH,
		WEST,
		SOUTH,
		EAST
	};

	class Vector2D {
	public:
		int X();
		int Y();


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