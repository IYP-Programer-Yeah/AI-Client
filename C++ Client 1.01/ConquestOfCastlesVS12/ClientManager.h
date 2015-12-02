#pragma once
#ifndef CLIENT_MANAGER
#define CLIENT_MANAGER

#include "Runnable.h"
#include "WorldModel.h"
#include "IPlayerAI.h"

using namespace ConquestOfCastles;

namespace ConquestOfCastles {
	class PlayerAiRunner : public Runnable {
	private:
		WorldModel* world;
		IPlayerAI* player_ai;
	public:
		PlayerAiRunner(WorldModel* world, IPlayerAI* player_ai);
		~PlayerAiRunner();
		void run() {
			player_ai->DoTurn(world);
		}
	};

	class ClientManager {
	private:
		char* server_port;
		char* server_address;
		char* player_name;
		IPlayerAI* player_ai;
		int cycle_time;
	public:
		ClientManager(char* server_address, char* server_port, char* player_name, IPlayerAI* player_ai);
		void Handle();
	};
}

#endif