#pragma once
#ifndef CLIENT_MANAGER
#define CLIENT_MANAGER

#include "WorldModel.h"
#include "IPlayerAI.h"

using namespace ConquestOfCastles;

namespace ConquestOfCastles {

	class ClientManager {
	public:
		ClientManager(char* server_address, char* server_port, char* player_name, IPlayerAI* player_ai);
		void Handle();
	};
}

#endif