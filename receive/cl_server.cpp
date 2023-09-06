#include "cl_server.h"

void cl_server::sock_bind() {
	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(12306);
	sock_addr.sin_addr.S_un.S_addr = ADDR_ANY;
	//inet_pton(AF_INET, ADDR_ANY, &sock_addr.sin_addr.S_un.S_addr);
	if (bind(slisten, (sockaddr*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
		printf("绑定套接字失败\n");
		return ;
	}
}

void cl_server::sock_listen(void) {
	if(listen(slisten, 10) == SOCKET_ERROR) {
		printf("监听客户连接失败\n");
		return;
	}
}

void cl_server::star_thread(int in_thread_num) {
	server_thread_arr = new cl_thread[in_thread_num];
	for (int i = 0; i < in_thread_num; i++) {
		server_thread_arr[i].create_thread();
	}
	thread_num = in_thread_num;
}

void cl_server::sock_select(void) {
	while (1) {
		timeval time = { 1,0 };
		fd_set fdset;
		FD_ZERO(&fdset);
		FD_SET(slisten, &fdset);
		if (select(NULL, &fdset, NULL, NULL, &time) == 0) {
			Sleep(1);
			continue;
		}

		SOCKADDR_IN client_add;
		int add_len = sizeof(client_add);
		SOCKET ser_conn_cli = accept(slisten, (sockaddr*)&client_add, &add_len);

		if (ser_conn_cli == SOCKET_ERROR) {
			printf("接收客户连接失败\n");
			closesocket(slisten);
			return;
		}

		char st_addr[15] = { 0 };
		inet_ntop(AF_INET, &client_add.sin_addr.S_un.S_addr, st_addr, sizeof(st_addr));

		cl_thread* min = server_thread_arr;
		for (int i = 1; i < thread_num; i++) {
			if (server_thread_arr[i].get_client_num() < min->get_client_num()) {
				min = &server_thread_arr[i];
			}
		}

		min->recv_client.push_back(ser_conn_cli);
		//server_thread_arr->recv_client.push_back(ser_conn_cli);
		//min->socket_change = true;
		printf("client ip:%s  port:%d  加入成功\n", st_addr, ntohs(client_add.sin_port));
	}
}

