#include <string>
#include <vector>

#include "rapidjson\document.h"

#include "Geometry.h"
#include "Unit.h"
#include "GameObjects.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

namespace ConquestOfCastles {

	Vector2D GoldMine::Pos() { return pos; }
	int GoldMine::GoldAmount() { return goldAmount; }
	GoldMine::GoldMine(Vector2D& pos, int goldAmount) : pos(pos), goldAmount(goldAmount) {}

	GoldMine::GoldMine(Value & data)
	{
		goldAmount = data["goldamount"].GetInt();
		pos = Vector2D(data["pos"]);
	}
}