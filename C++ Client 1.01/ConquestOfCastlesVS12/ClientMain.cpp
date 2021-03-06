#include "WorldModel.h"
#include "ClientManager.h"
#include "IPlayerAI.h"
#include "PlayerAI.h"

#include <string>

using namespace std;
using namespace ConquestOfCastles;

int main(int argc, char* argv[]) {

	char* player_name = "Arc";

	char* server_address;
	char* server_port;

	if (argc > 2) {
		server_address = argv[1];
		server_port = argv[2];
	}
	else {
		server_address = "localhost";
		server_port = "1111";
	}

	IPlayerAI* player_ai = new PlayerAI();

	ClientManager manager(server_address, server_port, player_name, player_ai);
	manager.Handle();

	return 0;
}