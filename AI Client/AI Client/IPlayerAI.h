#pragma once
#ifndef IPLAYERAI_H
#define IPLAYERAI_H

#include "WorldModel.h"

namespace ConquestOfCastles {
	class IPlayerAI {
	public:
		virtual void DoTurn(WorldModel* world) = 0;
	};
}
#endif