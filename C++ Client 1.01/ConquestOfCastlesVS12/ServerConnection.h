#pragma once
#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "TcpConnection.h"

#include <string>

using namespace std;

namespace ConquestOfCastles {
	class ServerConnection : public TcpConnection {
	private:

	public:
		ServerConnection(const char* address, const char* port) : TcpConnection(address, port) { TcpConnection::connect(); }
		int closeConnection();

		//Sending data
		int operator << (string& data);

		//Receiving data
		int operator >> (string& data);
	};
}

#endif