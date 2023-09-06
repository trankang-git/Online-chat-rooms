#pragma once
#include<string.h>
enum enum_msg
{
	Msg_Show,
	Msg_Join,
	Msg_Create,
	Msg_Talk,
	Exit
};
class cl_msg
{
public:	
	int msg_type;
	int size;
};

class cl_Msg_Show:public cl_msg
{
public:	
	cl_Msg_Show() {
		msg_type = Msg_Show;
		size = sizeof(cl_Msg_Show);
	}
};

class cl_Msg_Join :public cl_msg
{
	int room_id;

public:
	cl_Msg_Join(int roomid) {
		room_id = roomid;
		msg_type = Msg_Join;
		size = sizeof(cl_Msg_Join);
	}
	int get_room_id() {
		return room_id;
	}
};

class cl_Msg_Create :public cl_msg
{
public:

	cl_Msg_Create() {
		msg_type = Msg_Create;
		size = sizeof(cl_Msg_Create);
	}

};

class cl_Msg_Talk :public cl_msg
{
	char buff[1024];
	int room_id;
public:	
	cl_Msg_Talk(int id) {
		memset(buff, 0, sizeof(buff));
		msg_type = Msg_Talk;
		size = sizeof(cl_Msg_Talk);
		room_id = id;
	}
	char* get_buff_addr() {
		return buff;
	}
	int get_room_id() {
		return room_id;
	}
};

class cl_Exit :public cl_msg
{
public:
	cl_Exit() {
		msg_type = Exit;
		size = sizeof(cl_Exit);
	}
};