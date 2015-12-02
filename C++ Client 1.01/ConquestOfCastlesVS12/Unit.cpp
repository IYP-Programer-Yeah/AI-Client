#include "rapidjson\document.h"

#include "Unit.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

namespace ConquestOfCastles {

	UnitType Unit::Type() { return type; }
	int Unit::Id() { return id; }
	int Unit::Owner() { return owner; }
	int Unit::Hp() { return HP; }
	int Unit::Atk() { return ATK; }
	Vector2D Unit::Pos() { return pos; }
	Command* Unit::Command() { return cmd; }


	Unit::Unit(Value & data)
	{
		type = Parse(data["type"].GetString());
		id = data["id"].GetInt();
		owner = data["owner"].GetInt();
		Value& val = data["pos"];
		pos = Vector2D(data["pos"]);
		HP = data["HP"].GetInt();
		ATK = data["ATK"].GetInt();

		cmd = nullptr;
	}

	Unit::~Unit()
	{
		if (cmd != nullptr)
			delete cmd;
		cmd = nullptr;
	}

	void Unit::Move(Direction dir)
	{
		if (cmd != nullptr)
			delete cmd;
		cmd = new MoveCommand(id, pos[dir]);
	}

	void Unit::Attack(Direction dir)
	{
		if (cmd != nullptr)
			delete cmd;
		cmd = new AttackCommand(id, pos[dir]);
	}

	void Unit::Make(Direction dir, UnitType type)
	{
		if (cmd != nullptr)
			delete cmd;
		cmd = new MakeCommand(id, pos[dir], type);
	}

	string Unit::Parse(UnitType type)
	{
		switch (type) {
		case UnitType::WORKER:
			return "WORKER";
		case UnitType::WARRIOR:
			return "WARRIOR";
		case UnitType::CASTLE:
			return "CASTLE";
		}
		return "UNKNOWN";
	}

	UnitType Unit::Parse(string type)
	{

		if (type == "WORKER")
			return UnitType::WORKER;
		else if (type == "WARRIOR")
			return UnitType::WARRIOR;
		else if (type == "CASTLE")
			return UnitType::CASTLE;
		return UnitType::UNKNOWN;
	}

}