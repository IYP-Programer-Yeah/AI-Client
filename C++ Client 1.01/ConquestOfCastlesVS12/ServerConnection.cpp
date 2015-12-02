#include "ServerConnection.h"

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

namespace ConquestOfCastles {

	int ServerConnection::closeConnection()
	{
		TcpConnection::close();
		return 1;
	}

	int ServerConnection::operator << (string& s) {
		return TcpConnection::send((s + '\r' + '\n').c_str(), s.size() + 2);
	}

	int ServerConnection::operator >> (string& data) {
		string res = "";
		char buffer[1];
		while (TcpConnection::receive(buffer, sizeof(buffer))) {
			if (buffer[0] == '\n')
				break;
			if (buffer[0] != '\r')
				res += buffer[0];
		}
		data = res;
		return 0;
	}

}