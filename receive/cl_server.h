#pragma once

#include "../connect-service/SocketInit.hpp"
#include<vector>
#include<map>
#include"cl_thread.h"
#include <WS2tcpip.h>

#define wait_time 10

class cl_server
{
	SOCKET slisten;
	cl_thread* server_thread_arr;
	socket_init sock_init;
	int thread_num;

public:

	cl_server() {
		server_thread_arr = NULL;
		thread_num = 0;
		slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (slisten == SOCKET_ERROR) {
			printf("´´½¨Ì×½Ó×ÖÊ§°Ü\n");
			return;
		}
	}

	~cl_server() {
		closesocket(slisten);

		if (!server_thread_arr) {
			delete[] server_thread_arr;
		}

	}

	void sock_bind(void);
	void sock_listen(void);
	void star_thread(int thread_num);
	void sock_select(void);

};

