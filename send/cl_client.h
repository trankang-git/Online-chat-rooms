#pragma once
#include "../connect-service/SocketInit.hpp"
#include<ws2tcpip.h>

class cl_client
{
	socket_init socket_init;

public:
	SOCKET client_sock;

	cl_client() {
		client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (client_sock == SOCKET_ERROR) {
			printf("´´½¨Ì×½Ó×ÖÊ§°Ü\n");
			return ;
		}

	}

	~cl_client() {
		closesocket(client_sock);

	}

	void client_connect(const char* server_ip, u_short server_port);

};

