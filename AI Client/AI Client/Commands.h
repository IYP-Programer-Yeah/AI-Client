#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

using namespace ConquestOfCastles;
using namespace std;
namespace ConquestOfCastles {
	class Command {
	public:
	};

	class AttackCommand : public Command {
	public:
		AttackCommand(int id, Vector2D& pos);
		int Id();
		Vector2D* Position();
	};

	class MakeCommand : public Command {
	public:
		MakeCommand(int id, Vector2D& pos, UnitType type);
	};

	class MoveCommand : public Command {
	public:
		MoveCommand(int id, Vector2D& pos);
		int Id();
		Vector2D Position();
	};
}

#endif