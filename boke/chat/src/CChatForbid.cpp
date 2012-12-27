#include "CChatForbid.h"
#include <time.h>
#include <string.h>
#include "proto.hpp"
extern "C" {
#include <async_serv/net_if.h>
#include <libtaomee/log.h>
}

// 初始化，建立与游戏服务器的连接
bool CChatForbid::init(const char* ip, int port)
{
	memcpy(this->ip, ip, sizeof(this->ip));
	this->ip[15] = '\0';
	this->port = port;
	switch_fd = connect_to_svr(this->ip, this->port, 65535, 0);
	return true;
}

// 增加游戏服务器，如果当前列表中没有人，返回禁言时间
uint32_t CChatForbid::add_forbid_user(uint32_t userid)
{
	this->forbid_user_set.insert(userid);
	forbid_info_t fuser;
	fuser.userid = userid;
	fuser.forbid_time = time(NULL);
	this->forbid_user_list.push_back(fuser);
	return this->forbid_user_list.size() == 1 ? 300 : 0;
}

// 取消禁言，返回用户列表及下一次取消禁言的时间间隔
uint32_t CChatForbid::pop_forbid_user(std::vector<uint32_t>& userlist)
{
	forbid_info_t fuser = this->forbid_user_list.front();
	KDEBUG_LOG(fuser.userid, "POP USER\t[%u]", fuser.forbid_time);
	userlist.push_back(fuser.userid);
	this->forbid_user_list.pop_front();
	this->forbid_user_set.erase(fuser.userid);
	std::list<forbid_info_t>::iterator it = this->forbid_user_list.begin();
	while (it != this->forbid_user_list.end()) {
		if ((*it).forbid_time > fuser.forbid_time) 
			break;

		this->forbid_user_set.erase((*it).userid);
		it = this->forbid_user_list.erase(it);
		userlist.push_back((*it).userid);
		KDEBUG_LOG(it->userid, "POP USER\t[%u]", it->forbid_time);
	}
	
	return it == this->forbid_user_list.end() ? 0 : ((*it).forbid_time - fuser.forbid_time);
}

int CChatForbid::send_pkg_forbid_user(uint32_t userid)
{
	if (switch_fd == -1) {
		DEBUG_LOG("CONNECT TO SVR");
		switch_fd = connect_to_svr(this->ip, this->port, 65535, 0);
	}

	if (switch_fd == -1) {
		ERROR_LOG("fail to connect svr");
		return -1;
	}

	KDEBUG_LOG(userid, "SEND PKG TO GAME");

	char buff[256] = {0};
	svr_proto_t* pkg = (svr_proto_t *)buff;
	pkg->id = userid;
	pkg->len = sizeof(svr_proto_t) + 4;
	pkg->cmd = adm_forbid_chat;
	*(uint32_t *)pkg->body = 1;
	return net_send(switch_fd, pkg, pkg->len);
}

bool CChatForbid::try_reset_fd(int fd)
{
	if (fd == switch_fd) {
		switch_fd = connect_to_svr(this->ip, this->port, 65535, 0);
		DEBUG_LOG("CONNECT TO SVR\t[%d %d]", fd, switch_fd);
		return true;
	}

	return false;
}

bool CChatForbid::is_forbidden(uint32_t userid)
{
	return this->forbid_user_set.find(userid) != this->forbid_user_set.end();
}
