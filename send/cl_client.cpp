#include"cl_client.h"

void cl_client::client_connect(const char* server_ip, u_short server_port) {
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	inet_pton(AF_INET, server_ip, &server_addr.sin_addr.S_un.S_addr);

	if (connect(client_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		printf("客户端连接服务器失败！\n");
		return;
	}
}