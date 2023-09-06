#include"cl_client.h"
#include"../receive/cl_msg.h"

DWORD WINAPI th_fun(LPVOID lp) {
	SOCKET client = *(SOCKET*)lp;
	while (1) {

		fd_set fd;
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		timeval time = { 0,3 };

		if (select(NULL, &fd, NULL, NULL, &time) > 0) {
			for (int i = 0; i < fd.fd_count; i++) {
				char buff[1024] = { 0 };
				recv(fd.fd_array[i], buff, 1024, 0);
				printf("%s", buff);
			}
		}
		else {
			Sleep(1);
		}
	}

}

int main()
{

	HANDLE handle;

	cl_client a;

	a.client_connect("192.168.31.194", 12306);
	handle = CreateThread(NULL, NULL, th_fun, &a.client_sock, NULL, NULL);
	////创建套接字
	//SOCKET sclient =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;

	//if (sclient == SOCKET_ERROR) {
	//	printf("创建套接字失败\n");
	//	return -1;
	//}

	////连接服务器
	//
	//	sockaddr_in sock_in;
	//	sock_in.sin_family = AF_INET;
	//	sock_in.sin_port = htons(12306);
	//	inet_pton(AF_INET, "192.168.31.194", &sock_in.sin_addr.S_un.S_addr);
	//	if (connect(sclient, (const sockaddr*)&sock_in, sizeof(sock_in)) == SOCKET_ERROR) {
	//		printf("连接服务器失败\n");
	//		closesocket(sclient);
	//	}
	

	while (1) {
		char buff[1024] = {0};
		gets_s(buff);

		if (strncmp(buff, "show", strlen("show")) == 0) {
			cl_msg* send_data= new cl_Msg_Show;
			send(a.client_sock, (char*)send_data, send_data->size, 0);
		}

		else if (strncmp(buff, "join", strlen("join")) == 0) {
			int roomid = atoi(buff + strlen("join"));
			cl_msg* send_data = new cl_Msg_Join(roomid);
			send(a.client_sock, (char*)send_data, send_data->size, 0);
		}

		else if (strncmp(buff, "create", strlen("create")) == 0) {
			cl_msg* send_data = new cl_Msg_Create;
			send(a.client_sock, (char*)send_data, send_data->size, 0);
		}

		else if (strncmp(buff, "talk",4) == 0) {
			int room_id = atoi(buff + strlen("talk"));
			cl_Msg_Talk* send_data = new cl_Msg_Talk(room_id);

			//printf("开始聊天，输入leave离开聊天\n");
			//memset(buff, 0, sizeof(buff));
			gets_s(send_data->get_buff_addr(), 1024);
			while (strcmp(send_data->get_buff_addr(), "leave") != 0) {
				send(a.client_sock, (char *)send_data, send_data->size, 0);
				gets_s(send_data->get_buff_addr(), 1024);
			}
		}

		//send(a.client_sock, (char *)send_data, strlen(send_data), 0);
	}
	WaitForSingleObject(handle, 100);
	CloseHandle(&handle);

	system("pause");
	return 0;
}