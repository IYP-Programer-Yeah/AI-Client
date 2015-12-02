#include "Unit.h"
#include "Commands.h"

namespace ConquestOfCastles {

	AttackCommand::AttackCommand(int id, Vector2D& pos) : id(id), pos(pos) { }

	MakeCommand::MakeCommand(int id, Vector2D& pos, UnitType type) : id(id), pos(pos), type(type) {}

	MoveCommand::MoveCommand(int id, Vector2D& pos) : id(id), pos(pos) {}

	void AttackCommand::Serialize(Writer<StringBuffer>& writer)
	{
		writer.StartObject();
		writer.String("cmd");
		writer.String("attack");
		writer.String("id");
		writer.Int(id);
		writer.String("pos");

		pos.Serialize(writer);
	
		writer.EndObject();
	}
	void MakeCommand::Serialize(Writer<StringBuffer>& writer)
	{
		writer.StartObject();

		writer.String("cmd");
		writer.String("make");

		writer.String("id");
		writer.Int(id);

		writer.String("pos");
		pos.Serialize(writer);

		writer.String("type");
		writer.String(Unit::Parse(type).c_str());

		writer.EndObject();
	}
	void MoveCommand::Serialize(Writer<StringBuffer>& writer)
	{
		writer.StartObject();
		writer.String("cmd");
		writer.String("move");
		writer.String("id");
		writer.Int(id);
		writer.String("pos");
		pos.Serialize(writer);
		writer.EndObject();
	}
}