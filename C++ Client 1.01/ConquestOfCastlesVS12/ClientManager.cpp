#include "ServerConnection.h"
#include "ThreadManager.h"
#include "ClientManager.h"

#include <iostream>

using namespace ConquestOfCastles;
using namespace std;

namespace ConquestOfCastles {	

	ClientManager::ClientManager(char* server_address, char* server_port, char* player_name, IPlayerAI* player_ai) : server_port(server_port), server_address(server_address), player_name(player_name), player_ai(player_ai), cycle_time(1000) {}
	
	void ClientManager::Handle() {

		cout << "Server address: " << server_address << endl;
		cout << "Server port: " << server_port << endl;
		cout << "Cycle time: " << cycle_time << endl;
		cout << "Player name: \"" << player_name << "\"" << endl;

		try {

			ServerConnection connection(server_address, server_port);

			WorldModel* world = new WorldModel();

			//Registering Player
			{
				StringBuffer s;
				Writer<StringBuffer> writer(s);
				writer.StartObject();
				writer.String("name");
				writer.String(player_name);
				writer.EndObject();

				string register_player_json = s.GetString();

				connection << register_player_json;
				//LOG(DEBUG) << "SEND >> " << register_player_json;
			}

			//Setting Terrain
			string terrain_json;
			connection >> terrain_json;
			//LOG(DEBUG) << "RECEIVE >> " << terrain_json;

			Document terrain;
			terrain.Parse(terrain_json.c_str());
			world->SetTerrain(terrain["terrain"]);

			//Setting GoldMines
			string gold_mines_json;
			connection >> gold_mines_json;
			//LOG(DEBUG) << "RECEIVE >> " << gold_mines_json;

			Document gold_mines;
			gold_mines.Parse(gold_mines_json.c_str());

			world->SetGoldMines(gold_mines["objects"][0]);

			//Setting Player
			string player_json;
			connection >> player_json;
			//LOG(DEBUG) << "RECEIVE >> " << player_json;

			Document player;
			player.Parse(player_json.c_str());
			world->SetSelf(player);

			while (true) {
				//waiting for worldmodel
				string current_cycle_data_json;
				connection >> current_cycle_data_json;
				//LOG(DEBUG) << "RECEIVE >> " << current_cycle_data_json;

				Document world_json;
				world_json.Parse(current_cycle_data_json.c_str());

				delete world;
				world = new WorldModel(world_json);

				//running player ai
				Runnable* player_ai_runner = new PlayerAiRunner(world, player_ai);
				ThreadManager::submit(player_ai_runner);
				ThreadManager::sleep(cycle_time);
				ThreadManager::kill(player_ai_runner);
				delete player_ai_runner;

				//making data to send;
				{
					StringBuffer s;
					Writer<StringBuffer> writer(s);

					writer.StartObject();
					writer.String("cmds");
					writer.StartArray();
					for (Unit* unit : world->Self()->Agents()) {
						//LOG(DEBUG) << unit;
						if (unit->Command() != nullptr)
							unit->Command()->Serialize(writer);
						else cerr << "Unit " << Unit::Parse(unit->Type()) << " has no command." << endl;
					}
					writer.EndArray();
					writer.EndObject();

					//Sending data
					string send_data = s.GetString();
					//LOG(DEBUG) << "SEND >> " << send_data;
					connection << send_data;
				}
			}
		}
		catch (ConnectToServerFailureException e) {
			cerr << "Exiting application." << endl;
			exit(1);
		}
		catch (ConnectionClosedException e) {
			cerr << "Finishing application." << endl;
			exit(0);
		}
		catch (ThreadCreationFailedException e) {
			cerr << "Thread failed to create." << endl;
			exit(0);
		}
		catch (NetworkException e)
		{
			exit(0);
		}
	}

	PlayerAiRunner::PlayerAiRunner(WorldModel* world, IPlayerAI* player_ai) : world(world), player_ai(player_ai) {}

	PlayerAiRunner::~PlayerAiRunner() {}
}