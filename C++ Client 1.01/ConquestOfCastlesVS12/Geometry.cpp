#include "Serializable.h"
#include "Geometry.h"

#include "rapidjson\document.h"
#include "rapidjson\writer.h"

#include <cmath>

using namespace ConquestOfCastles;
using namespace rapidjson;
using namespace std;

namespace ConquestOfCastles {

	int Vector2D::X() {
		return x;
	}

	int Vector2D::Y() {
		return y;
	}

	Vector2D::Vector2D() : x(0), y(0) {}

	Vector2D::Vector2D(int x, int y) : x(x), y(y) {}
	

	void Vector2D::Serialize(Writer<StringBuffer>& writer) {
		writer.StartObject();
		writer.String("x");
		writer.Int(x);
		writer.String("y");
		writer.Int(y);
		writer.EndObject();
	}

	Vector2D::Vector2D(Value & data)
	{
		x = data["x"].GetInt();
		y = data["y"].GetInt();
	}

	Vector2D Vector2D::operator+(Vector2D & vector2d)
	{
		return Vector2D(vector2d.x + x, vector2d.y + y);
	}

	Vector2D Vector2D::operator-(Vector2D & vector2d)
	{
		return Vector2D(x - vector2d.x, y - vector2d.y);
	}

	Vector2D Vector2D::operator+=(Vector2D & vector2d)
	{
		x += vector2d.x;
		y += vector2d.y;
		return *this;
	}

	Vector2D Vector2D::operator-=(Vector2D & vector2d)
	{
		x -= vector2d.x;
		y -= vector2d.y;
		return *this;
	}

	bool Vector2D::operator==(Vector2D & vector2d)
	{
		return vector2d.x == x && vector2d.y == y;
	}

	double Vector2D::Length()
	{
		return sqrt(x*x + y*y);
	}

	double Vector2D::Distance(Vector2D vector2d)
	{
		return ((*this)-vector2d).Length();
	}

	Vector2D Vector2D::operator[](Direction direction)
	{
		switch (direction) {
		case NORTH:
			return Vector2D(x, y - 1);
		case WEST:
			return Vector2D(x - 1, y);
		case SOUTH:
			return Vector2D(x, y + 1);
		case EAST:
			return Vector2D(x + 1, y);
		}
		return *this;
	}
}