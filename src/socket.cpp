#include "socket.h"
#include <string>
#include <vector>

#include "misc.h"


using namespace erebos::socket;

#ifdef WINDOWS

#define WINDOWS_LEAN_AND_MEAN 1
#define _WIN32_WINNT 0x501
#include <windows.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <ws2tcpip.h>

#elif defined(LINUX)
//
#endif


bool erebos::socket::initialized = false;


int erebos::socket::initialize() {

#ifdef WINDOWS

	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
		return 1;

#endif

	return 0;
}

void erebos::socket::destroy() {

#ifdef WINDOWS

	if(initialized)
		WSACleanup();

#endif
}

std::string forge_http_packet(HTTPRequest request) {

}


TCPSocket::TCPSocket() {
	// Initialize WinSock (on Windows)
	if(!initialized)
		if(!initialize())
			initialized = true;

	open = false;
	host_entity = nullptr;
}


TCPSocket::~TCPSocket() {

	close();

	if(host_entity)
#ifdef WINDOWS
		delete (SOCKET*) host_entity;
#elif defined(LINUX)
		delete (hostent*) host_entity;
#endif
}


int TCPSocket::connect(std::string hostname, unsigned int port) {

	if(!initialized)
		return 1;

#ifdef WINDOWS

	struct addrinfo *result = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int err = getaddrinfo(hostname.c_str(), std::to_string(port).c_str(), &hints, &result);

	SOCKET sock = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if(sock == INVALID_SOCKET) {
		freeaddrinfo(result);
		return -1;
	}

	err = ::connect(sock, result->ai_addr, (int) result->ai_addrlen);

	freeaddrinfo(result);

	if(err == SOCKET_ERROR) {

		closesocket(sock);
		return -2;
	}

	SOCKET* buff = new SOCKET();
	memcpy(buff, &sock, sizeof(SOCKET));
	host_entity = (void*) buff;

	open = true;

	return 0;

#elif defined(LINUX)

	return 0;

#endif
}


int TCPSocket::read(char* buffer, unsigned int packetsize) {

	if(!initialized || !open)
		return -2;

#ifdef WINDOWS

	SOCKET sock = *((SOCKET*) host_entity);

	std::vector<char*> data;
	char* packet = new char[packetsize];
	unsigned int totalsize = 0;
	int size = 0;

	do {

		size = recv(sock, packet, packetsize, 0);

		if(size < 0) {

			for (unsigned int i = 0; i < data.size(); ++i)
				delete data[i];
			return -1;
		}

		data.emplace_back(packet);
		packet = new char[packetsize];
		totalsize += size;

	} while(size > 0);

	if(!totalsize) {
		buffer = nullptr;
		return 1;
	}

	buffer = new char[totalsize];

	for (unsigned int i = 0; i < data.size(); ++i) {

		if(i != data.size() - 1)
			memcpy((void*) (intptr_t) buffer[i * packetsize], (void*) data[i], packetsize);
		else
			memcpy((void*) (intptr_t) buffer[i * packetsize], (void*) data[i], totalsize % packetsize);

		delete data[i];
	}


#elif defined(LINUX)
//
#endif

	return 0;
}


int TCPSocket::write(std::string data) {

	if(!initialized || !open)
		return -2;

#ifdef WINDOWS

	SOCKET sock = *((SOCKET*) host_entity);

	int err = send(sock, data.c_str(), data.size(), 0);
	if(err == SOCKET_ERROR)
		return -1;

#elif defined(LINUX)
//
#endif

	return 0;
}


//int TCPSocket::write(std::unique_result<char[]> data, size_t size) {}

int TCPSocket::close() {

	if(!initialized || !open)
		return -2;

#ifdef WINDOWS

	SOCKET sock = *((SOCKET*) host_entity);
	closesocket(sock);

#elif defined(LINUX)


#endif

	return 0;
}


