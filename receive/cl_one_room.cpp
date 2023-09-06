#include "cl_one_room.h"

void cl_room_manage::create_one_room(SOCKET& client, int& room_id) {
		EnterCriticalSection(&m_sec);

		if (room_id_sequence.size()==0) {
			room_id = 0;
		}

		else {
			cl_one_room one_room;
			one_room.online_num = 1;
			one_room.room_id = room_id_sequence.front();
			one_room.room_member.insert(client);

			room_id_sequence.pop();

			room_arr[one_room.room_id] = one_room;

			room_id = one_room.room_id;

		}

		LeaveCriticalSection(&m_sec);
}

void cl_room_manage::show_all_room(SOCKET& client) {

	for (auto iter = room_arr.begin(); iter != room_arr.end(); iter++) {
		std::string s_temp=std::to_string(iter->first)+"  ";

		send(client, s_temp.c_str(), s_temp.size(), 0);
	}

	send(client, "\n", strlen("\n"), 0);
}

bool cl_room_manage::join_one_room(SOCKET& client, int room_id) {
	auto iter = room_arr.find(room_id);

	if (iter == room_arr.end()) {
		send(client, "����Ų����ڣ��޷����뷿��\n", strlen("����Ų����ڣ��޷����뷿��\n"), 0);

		return false;
	}

	if (iter->second.room_member.size() >= room_member_MAX) {
		send(client, "������Ա�������޷����뷿��\n", strlen("������Ա�������޷����뷿��\n"), 0);

		return false;
	}

	if (iter->second.room_member.find(client) != iter->second.room_member.end()) {
		send(client, "�����ڷ�����\n", strlen("�����ڷ�����\n"), 0);

		return false;
	}

	iter->second.room_member.insert(client);
	iter->second.online_num++;

	std::string s_temp = "�ͻ���"+std::to_string(client) + "����ɹ�����������" + std::to_string(iter->second.online_num) + "/" + std::to_string(room_member_MAX) + "\n";

	for (auto iter_set = iter->second.room_member.begin(); iter_set != iter->second.room_member.end(); iter_set++) {
		send(*iter_set, s_temp.c_str(), s_temp.size(), 0);
	}

	return true;
}

void cl_room_manage::talk_to_other(SOCKET& client, int room_id, cl_Msg_Talk* client_msg_talk) {
	auto iter_id = room_arr.find(room_id);
	if (iter_id == room_arr.end()) {
		send(client, "���䲻����\n", strlen("���䲻����\n"), 0);
		return;
	}

	auto iter_client = iter_id->second.room_member.find(client);
	if (iter_client == iter_id->second.room_member.end()) {
		send(client, "�㲻�ڸ÷�����\n", strlen("�㲻�ڸ÷�����\n"), 0);
		return;
	}

	for (auto iter_temp = iter_id->second.room_member.begin(); iter_temp != iter_id->second.room_member.end(); iter_temp++) {
		if (iter_temp != iter_client)
		{
			std::string s_temp = "---�ͻ���" + std::to_string(client) + "���͵���Ϣ---\n";
			send(*iter_temp, s_temp.c_str(), s_temp.size(), 0);

			send(*iter_temp, client_msg_talk->get_buff_addr(), strlen(client_msg_talk->get_buff_addr()), 0);

			send(*iter_temp, "\n------------\n", strlen("\n------------\n"), 0);
		}
		
	}
}