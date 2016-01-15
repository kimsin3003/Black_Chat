#include "stdafx.h"
#include "ChatServer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")



ChatServer::ChatServer()
{
	char *escape = "/quit";	// ���� ���
	char readline[LINE];	// read buffer
	char *start = "Now you connected Server\n";		// ���Ӿ˸�
	int	i, j, n, addrlen;
	SOCKET clilen;		// ���� ����
	unsigned short	port;
	struct sockaddr_in clientd_addr;	// ���� �ּ�
	WSADATA wsa;		// �������� ���ϼ���
	int	iError;
	m_chatuser = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {		// ���� �ʱ�ȭ
		exit(1);
	}


	if ((m_listeningSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {		// ���� ����
		printf("fail make socket\n");
		exit(0);
	}

	port = SERV_PORT;
	ZeroMemory(&m_server_addr, sizeof(m_server_addr));		// �ʱ�ȭ
	m_server_addr.sin_family = AF_INET;			// ���� �ɼ� ����
	m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_server_addr.sin_port = htons(port);

	if (bind(m_listeningSock, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr)) < 0) {
		printf("fail bind\n");
		exit(0);
	}

	if (listen(m_listeningSock, SOMAXCONN) == -1)
	{
		printf("failed to listen");
	}
	m_maxfd = m_listeningSock + 1;

}


void ChatServer::DisconnectClient(int i)
{
	closesocket(m_client_s[i].socket);	// i��° ���� ����
	if (i == m_chatuser - 1) {
		m_client_s[i] = m_client_s[m_chatuser - 1];
		m_chatuser--;		// �������� ����
		printf("Now On the net %d users\n", m_chatuser);
	}
}

/* ���� ä�� �����ڼ��� �˻� */
int ChatServer::UserNum(int user)
{
	unsigned int max = user;
	int i;

	for (i = 0; i < m_chatuser; i++) {
		if (max < m_client_s[i].socket)
			max = m_client_s[i].socket;
	}

	return max;
}


void ChatServer::Start()
{
	struct sockaddr_in clientd_addr;
	int clilen;
	SOCKET clientSock;
	int	iError;
	char* start = "Welcome to Black Chat";
	char* login = "logged in";

	while (1)
	{

		FD_ZERO(&m_read_fds);		// ���� ��ũ���� set �ʱ�ȭ
		FD_SET(m_listeningSock, &m_read_fds);	//listen�ϰ� �ִ� ���Ͽ� �Է��� �ִ��� �˻��ϱ� ���� ��ũ���� set�� �߰�

		for (int i = 0; i < m_chatuser; i++) {
			FD_SET(m_client_s[i].socket, &m_read_fds);
		}

		m_maxfd = UserNum(m_listeningSock) + 1;


		//��ũ���� set �ȿ��� ��� fd�� �Է��� ���Դ��� ǥ��
		if (select(m_maxfd, &m_read_fds, (fd_set *)0, (fd_set *)0, NULL) < 0) {
			iError = WSAGetLastError();
			printf("fail select function\n");
			exit(0);
		}

		if (FD_ISSET(m_listeningSock, &m_read_fds)) {
			// ���ϵ�ũ���Ϳ� ���� �����Ͱ� ������
			clilen = sizeof(clientd_addr);
			clientSock = accept(m_listeningSock, (struct sockaddr *)&clientd_addr, &clilen);

			if (m_listeningSock == -1) {
				printf("fail accept\n");
				exit(0);
			}

// 			//id ���� recv.
// 			if (recv(m_listeningSock, m_client_s[m_chatuser].id, sizeof(m_client_s[m_chatuser].id), 0)){
// 				send(m_listeningSock, login, strlen(login), 0);
// 			}

			m_client_s[m_chatuser].socket = clientSock;
			m_client_s[m_chatuser].logged = false;
			m_chatuser++;

			send(m_listeningSock, start, strlen(start), 0);
			printf("%d user connected\n", m_chatuser);
			if (listen(m_listeningSock, SOMAXCONN) == -1)
			{
				printf("failed to listen");
			}
		}

		//��ε� ĳ����
		for (int i = 0; i < m_chatuser; i++) {		// ������ �ִ� ��������ŭ
			char readline[LINE];
			int n;

			memset(readline, '\0', LINE);
			if (FD_ISSET(m_client_s[i].socket, &m_read_fds)) {		// ���� ��ũ���� ���� Ȯ��
				if ((n = recv(m_client_s[i].socket, readline, LINE, 0)) <= 0) {
					DisconnectClient(i);
					continue;
				}

				if (strstr(readline, "/quit")){		// FIXME : ����� ������ ���� Ű���� ó�� ����
					DisconnectClient(i); // ���� ���� ����
					continue;
				}

				readline[n] = 0;

				if (!m_client_s[i].logged){
					strcpy(m_client_s[i].id, readline);
					m_client_s[i].logged = true;
				}
				else{
					for (int j = 0; j < m_chatuser; j++) {	// ��ε�ĳ����
						send(m_client_s[j].socket, m_client_s[i].id, strlen(m_client_s[i].id), 0);
						send(m_client_s[j].socket, readline, n + 1, 0);
					}
				}
			}
		}
	}
}

void ChatServer::BroadCast()
{

}

ChatServer::~ChatServer()
{
}
