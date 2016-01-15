#pragma once

#include <WinSock2.h>
#define LINE 100000	
#define MAXCLIENT	5
#define	SERV_PORT	8787

typedef struct client_t
{
	unsigned int socket;
	char id[20];
	bool logged;
}CLIENT;

class ChatServer
{
public:
	ChatServer();
	~ChatServer();
	void Start();

private:
	void DisconnectClient(int i);
	int UserNum(int user);

	void BroadCast();
	int m_maxfd;
	int m_chatuser;	// 채팅 참가자 수
	CLIENT m_client_s[MAXCLIENT];
	SOCKET m_listeningSock;
	fd_set m_read_fds;
	struct sockaddr_in m_server_addr;	// 소켓 주소
};

