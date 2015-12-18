#pragma once
#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "WorldModel.h"
#include "IPlayerAI.h"
#include <cstdlib>
#include <ctime>

using namespace std;

namespace ConquestOfCastles {

	class Random {
	public:
		Random() {
			srand(time(0));
		}
		int next_int() {
			return ((rand() << 15 + rand()) & ((1 << 24) - 1)) / (1 << 24);
		}
		double next_double(){
			rand();
			return static_cast<double>(next_int() % 10000) / 10000.0;
		}
	};

	class PlayerAI : public IPlayerAI {
	private:
		
	public:
		PlayerAI() {
			srand(time(0));
		}

		void DoTurn(WorldModel* world);
	};
}

#endif