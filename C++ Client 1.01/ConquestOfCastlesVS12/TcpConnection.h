#pragma once
#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#ifdef _WIN32

#define _WINSOCKAPI_

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#endif

#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

namespace ConquestOfCastles {
	

	class TcpConnection {

	private:

		const char* hostname;
		const char* port;

#ifdef _WIN32

		SOCKET ConnectSocket;
		int iResult;
		WSADATA wsaData;

		addrinfo *result,
			*ptr,
			hints;

#elif LINUX

#endif

	public:
		TcpConnection(const char* hostname,
			const char* port);

		~TcpConnection();

		int connect();

		int close();

		int send(const char * data,
			const unsigned int len);

		int receive(char * buf,
			const unsigned int len);

	};

	class NetworkException : public std::runtime_error {
	private:
	const char* make_error(const char* error, const int error_code) {
			std::string e(error);
			e += error_code;
			return e.c_str();
		}
	public:
		NetworkException(const char* error, const int error_code) : std::runtime_error(make_error(error, error_code)) {
			cerr << error << ": " << error_code << endl;
		}
	};

#ifdef _WIN32
	class WSAStartupFailureException : public NetworkException {
	public:
		WSAStartupFailureException(int error_code) : NetworkException("WSA Startup failed with error: ", error_code) {}
	};
#endif

	class DNSLookupFailureException : public NetworkException {
	public:
		DNSLookupFailureException(int error_code) : NetworkException("DNS Lookup failed with code:  ", error_code){}
	};

	class SocketCreationFailureException : public NetworkException {
	public:
		SocketCreationFailureException(int error_code) : NetworkException("Socket creation failed with error: ", error_code) {}
	};

	class ConnectToServerFailureException : public NetworkException {
	public:
		ConnectToServerFailureException(int error_code) : NetworkException("Connect to server failed with error: ", error_code) {}
	};

	class ConnectionClosedException : public NetworkException {
	public:
		ConnectionClosedException() : NetworkException("Connection Closed.", 0) {}
	};

	class SendFailureException : public NetworkException {
	public:
		SendFailureException(int error_code) : NetworkException("Send failed with error: ", error_code) {}
	};

	class ReceiveFailureException : public NetworkException {
	public:
		ReceiveFailureException(int error_code) : NetworkException("Receive failed with error: ", error_code) {}
	};
}
#endif