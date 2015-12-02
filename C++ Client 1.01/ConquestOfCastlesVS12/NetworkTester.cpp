#include "ServerConnection.h"
#include "ThreadManager.h"
#include "easylogging++.h"

#include <iostream>
#include <string>

using namespace ConquestOfCastles;
using namespace std;

// Sending objects on stack without pointer causes them to terminate! :\
// If i send connection to constructor of this method by ServerConnection not ServerConnection* it will be fucked
// and terminates the connection! :/
// Using ServerConnection& is also working...
// What are the difference between these shits?

class StreamReader : public Runnable{
private:
	ServerConnection connection;
public:
	StreamReader(ServerConnection& connection) : connection(connection) {}
	void run(void) {
		string in;
		while (true) {
			connection >> in;
			cout << in << endl;
		}
	}
};

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
	ServerConnection connection("localhost", "6985");
	StreamReader* reader = new StreamReader(connection);
	ThreadManager::submit(reader);

	string in;
	while (true) {
		getline(cin, in);
		connection << in;
	}
	connection.closeConnection();
	return 0;
}	