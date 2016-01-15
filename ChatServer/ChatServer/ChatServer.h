#pragma once

#include <WinSock2.h>
#define LINE		1024
#define MAXCLIENT	5
#define	SERV_PORT	8787
class ChatServer
{
public:
	ChatServer();
	~ChatServer();

private:
	void DisconnectClient(int i);
	int UserNum(int user);
	void Accept();

	void BroadCast();
	int m_maxfd;
	int m_chatuser;	// 채팅 참가자 수
	unsigned int m_client_s[MAXCLIENT];
	SOCKET m_listeningSock, clilen;
	fd_set m_read_fds;
	struct sockaddr_in m_server_addr;	// 소켓 주소
};

