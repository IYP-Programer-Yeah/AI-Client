#ifdef _WIN32

#include "TcpConnection.h"
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;

namespace ConquestOfCastles {

	TcpConnection::TcpConnection(
		const char* hostname,
		const char* port) : hostname(hostname), port(port) {

		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			throw WSAStartupFailureException(WSAGetLastError());
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
	}

	TcpConnection::~TcpConnection() {
		close();
	}

	int TcpConnection::close() {
		closesocket(ConnectSocket);
		WSACleanup();
		return 0;
	}

	int TcpConnection::connect() {

		cout << "Attempting to connect to " << hostname << " on port " << port << endl;

		iResult = getaddrinfo(hostname, port, &hints, &result);
		if (iResult != 0) {
			WSACleanup();

			throw DNSLookupFailureException(WSAGetLastError());
		}

		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				WSACleanup();
				throw SocketCreationFailureException(WSAGetLastError());
			}

			// Connect to server.
			//::connect calls global connect
			iResult = ::connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);
		if (ConnectSocket == INVALID_SOCKET) {
			WSACleanup();
			throw ConnectToServerFailureException(WSAGetLastError());
		}

		cout << "Connection established." << endl;

		return 0;
	}

	int TcpConnection::send(const char * data,
		const unsigned int len) {

		//::send refers to global send
		iResult = ::send(ConnectSocket, data, len, 0);

		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			WSACleanup();
			throw SendFailureException(WSAGetLastError());
		}

		return 0;

	}

	int TcpConnection::receive(char * buf,
		const unsigned int len) {

		iResult = ::recv(ConnectSocket, buf, len, 0);

		if (iResult == 0)
			throw ConnectionClosedException();
		if (iResult < 0)
			throw ReceiveFailureException(WSAGetLastError());

		return iResult;
	}
}

#endif