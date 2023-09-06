#include "cl_thread.h"
#include<string>
#include"cl_one_room.h"

cl_room_manage room_manage_cl;

DWORD WINAPI cl_thread::th_fun(LPVOID lp) {
	cl_thread *thread_cl = ((cl_thread*)lp);
	while (1) {
		if (!thread_cl->recv_client.empty()|| thread_cl->socket_change) {//�������ı���SOCKET����

			printf("............\n");//�����̴߳��������
			printf("....%d.....\n", GetCurrentThreadId() );
			for (auto a : thread_cl->recv_client) {
				thread_cl->thread_recv_client.insert(a);
			}
			thread_cl->recv_client.clear();

			int i = 0;//����fdset
			for (auto iter = thread_cl->thread_recv_client.begin(); iter != thread_cl->thread_recv_client.end(); iter++,i++) {
				printf(".socket...%lld.....\n", *iter);
				thread_cl->fdset.fd_array[i] = *iter;
			}
			thread_cl->fdset.fd_count = thread_cl->thread_recv_client.size();

			thread_cl->socket_change = false;
		}

		fd_set temp_fdset = thread_cl->fdset;
		timeval time = { 1,0 };
		if (select(NULL, &temp_fdset, NULL, NULL, &time) > 0) {
			for (int i = 0; i < temp_fdset.fd_count; i++) {
				char buff[sizeof(cl_Msg_Talk)] = {0};
				int test=recv(temp_fdset.fd_array[i], buff, sizeof(cl_Msg_Talk), 0);
				if (test > 0) {
					cl_msg* client_msg = (cl_msg*)buff;

					switch (client_msg->msg_type){

						case Msg_Show: {
							printf("�ͻ���%lld������ʾ������\n", temp_fdset.fd_array[i]);

							send(temp_fdset.fd_array[i], "-----����������----\n", strlen("-----����������----\n"), 0);
							room_manage_cl.show_all_room(temp_fdset.fd_array[i]);
							send(temp_fdset.fd_array[i], "------------------------\n", strlen("------------------------\n"), 0);

							break;
						}

						case Msg_Join: {
							cl_Msg_Join* client_msg_join = (cl_Msg_Join *) client_msg;
							printf("�ͻ���%lld���󣺼���%d��������!\n", temp_fdset.fd_array[i], client_msg_join->get_room_id());

							room_manage_cl.join_one_room(temp_fdset.fd_array[i], client_msg_join->get_room_id());

							break;
						}

						case Msg_Create: {
							cl_Msg_Create* client_msg_join = (cl_Msg_Create*)client_msg;
							printf("�ͻ���%lld���󣺴���������!\n", temp_fdset.fd_array[i]);

							int room_id;
							room_manage_cl.create_one_room(temp_fdset.fd_array[i], room_id);

							if (room_id>0) {
								std::string s_temp = "��������ɹ��������Ϊ:" + std::to_string(room_id)+"\n";
								send(temp_fdset.fd_array[i], s_temp.c_str(), s_temp.size(), 0);
							}

							else {
								send(temp_fdset.fd_array[i], "��������ʧ��\n", strlen("��������ʧ��\n"), 0);
							}
							break;
						}

						case Msg_Talk: {
							cl_Msg_Talk* client_msg_talk = (cl_Msg_Talk*)client_msg;
							printf("�ͻ���%lld������Ϣ����%d��%s\n", temp_fdset.fd_array[i], test, client_msg_talk->get_buff_addr());

							room_manage_cl.talk_to_other(temp_fdset.fd_array[i], client_msg_talk->get_room_id(), client_msg_talk);

							break;
						}

						default: {
							printf("�ͻ���%lld������Ϣ:��Ϣ����ʧ��...%s\n", temp_fdset.fd_array[i],buff);
							break;
						}
					}
					//printf("�ͻ���%lld��Ϣ��%s\n", temp_fdset.fd_array[i],buff);
				}

				else {
					if (thread_cl->thread_recv_client.find(temp_fdset.fd_array[i]) != thread_cl->thread_recv_client.end()) {
						thread_cl->thread_recv_client.erase(temp_fdset.fd_array[i]);
					}

					thread_cl->socket_change = true;

					printf("�ͻ��˶Ͽ�����\n");
					break;
				}
			}
		}
	}
}

void cl_thread::create_thread(void) {
	thread_handle = CreateThread(0, 0, th_fun, (LPVOID)this, 0, 0);
}

int cl_thread::get_client_num(void) {
	return thread_recv_client.size();
}