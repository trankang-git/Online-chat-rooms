#include "../connect-service/SocketInit.hpp"
#include"cl_server.h"

int main()
{

	cl_server a;
	a.sock_bind();
	a.sock_listen();
	a.star_thread(3);
	a.sock_select();
	
	////�����׽���

	//SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//if (slisten == SOCKET_ERROR) {
	//	printf("�����׽���ʧ��\n");
	//	return -1;
	//}

	////���׽���
	//sockaddr_in sock_in;
	//sock_in.sin_family = AF_INET;
	//sock_in.sin_port = htons(12345);
	//sock_in.sin_addr.S_un.S_addr = ADDR_ANY;

	//if (bind(slisten, (const sockaddr*)&sock_in, sizeof(sock_in)) == SOCKET_ERROR) {
	//	printf("���׽���ʧ��\n");
	//	closesocket(slisten);
	//	return -1;
	//}

	////�����ͻ�����
	//if (listen(slisten, 5) == SOCKET_ERROR) {
	//	printf("�����ͻ�����ʧ��\n");
	//	closesocket(slisten);
	//	return -1;
	//}

	//fd_set fd_read;
	//FD_ZERO(&fd_read);
	//FD_SET(slisten, &fd_read);
	//timeval tv = { 1,0 };

	//while (1) {
	//	fd_set temp = fd_read;
	//	if (select(NULL, &temp, NULL, NULL, &tv) == 0) {
	//		Sleep(1);
	//		continue;
	//	}
	//	for (int i = 0; i < temp.fd_count; i++) {
	//		if (temp.fd_array[i] == slisten) {//�пͻ������ӷ�����
	//			sockaddr_in client_addr;
	//			int addr_size = sizeof(client_addr);
	//			SOCKET sc_client=accept(slisten, (sockaddr*)&client_addr, &addr_size);

	//			if (sc_client == SOCKET_ERROR) {
	//				printf("���տͻ�����ʧ��\n");
	//				closesocket(slisten);
	//				return -1;
	//			}

	//			char st_addr[15] = {0};
	//			inet_ntop(AF_INET, &client_addr.sin_addr.S_un.S_addr, st_addr,sizeof(st_addr));
	//			printf("client ip:%s  port:%d\n", st_addr, ntohs(client_addr.sin_port));

	//			FD_SET(sc_client, &fd_read);
	//		}
	//		else {//�ͻ��˷�����Ϣ
	//			char buf[1024];
	//			if (recv(temp.fd_array[i], buf, 1024, 0) > 0) {
	//				printf("�ͻ�����Ϣ��%s\n", buf);
	//			}
	//			else {
	//				FD_CLR(temp.fd_array[i], &fd_read);
	//				printf("�ͻ��˶Ͽ�����\n");
	//				break;
	//			}
	//		}
	//	}
	//}

	//closesocket(slisten);

	system("pause");
	return 0;
}