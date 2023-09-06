#pragma once
#include<vector>
#include<set>
#include<windows.h>
#include"cl_msg.h"

class cl_thread
{
	std::set<SOCKET> thread_recv_client; //线程实际处理的SOCKET数组
	fd_set fdset;
	HANDLE thread_handle;

public:
	std::vector<SOCKET> recv_client; //连接服务器和线程的中间SOCKET数组
	bool socket_change;

	cl_thread() {
		socket_change = false;
		thread_handle = NULL;
		FD_ZERO(&fdset);
	}

	~cl_thread() {

		if (thread_handle != NULL) {
			WaitForSingleObject(thread_handle, INFINITE);
			CloseHandle(thread_handle);
		}

		if (!recv_client.empty()) {//清空
			for (auto a : recv_client) {
				closesocket(a);
			}
		}

		if (!thread_recv_client.empty()) {
			for (auto a : thread_recv_client) {
				closesocket(a);
			}
		}
	}

	void create_thread(void);
	static DWORD WINAPI th_fun(LPVOID lp);
	int get_client_num(void);

};

