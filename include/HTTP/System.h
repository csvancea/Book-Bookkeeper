#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
	#include <WS2tcpip.h>
#else // LINUX
	#include <unistd.h>
	#include <netinet/ip.h>
	#include <netdb.h>

	#define INVALID_SOCKET (-1)
	#define SOCKET_ERROR (-1)

	#define closesocket close

	typedef int SOCKET;
#endif
