#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include "Geometry.h"
#include "Serializable.h"
#include "UnitType.h"

#include "rapidjson\writer.h"

using namespace ConquestOfCastles;
using namespace std;
using namespace rapidjson;

namespace ConquestOfCastles {
	class Command : public Serializable {
	public:
		virtual void Serialize(Writer<StringBuffer>& writer) = 0;
	};

	class AttackCommand : public Command {
	private:
		int id;
		Vector2D pos;
	public:
		AttackCommand(int id, Vector2D& pos);
		
		void Serialize(Writer<StringBuffer>& writer);
	};

	class MakeCommand : public Command {
	private:
		int id;
		UnitType type;
		Vector2D pos;
	public:
		MakeCommand(int id, Vector2D& pos, UnitType type);

		void Serialize(Writer<StringBuffer>& writer);
	};

	class MoveCommand : public Command {
	private:
		int id;
		Vector2D pos;
	public:
		MoveCommand(int id, Vector2D& pos);

		void Serialize(Writer<StringBuffer>& writer);
	};
}

#endif