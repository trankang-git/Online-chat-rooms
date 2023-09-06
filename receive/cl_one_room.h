#pragma once
#include<set>
#include<map>
#include<string>
#include<windows.h>
#include<queue>
#include"cl_msg.h"

#define room_member_MAX 50
#define room_num_MAX 50

class cl_one_room
{
public:
	int room_id;
	std::set<SOCKET> room_member;
	int online_num;
};

class cl_room_manage {
	CRITICAL_SECTION m_sec;
	std::map<int,cl_one_room> room_arr;
	std::queue<int> room_id_sequence;
public:
	cl_room_manage() {

		for (int i = 1; i < room_num_MAX; i++) {
			room_id_sequence.push(i);
		}

		InitializeCriticalSection(&m_sec);
	}
	~cl_room_manage(){
		DeleteCriticalSection(&m_sec);
	}

	void create_one_room(SOCKET& client,int &room_id);
	void show_all_room(SOCKET& client);
	bool join_one_room(SOCKET& client, int room_id);
	void talk_to_other(SOCKET& client,int room_id, cl_Msg_Talk* client_msg_talk);
};
