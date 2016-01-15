#include "stdafx.h"
#include "ChatServer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")



ChatServer::ChatServer()
{
	char *escape = "/quit";	// 종료 명령
	char readline[LINE];	// read buffer
	char *start = "Now you connected Server\n";		// 접속알림
	int	i, j, n, addrlen;
	SOCKET clilen;		// 소켓 변수
	unsigned short	port;
	struct sockaddr_in clientd_addr;	// 소켓 주소
	WSADATA wsa;		// 윈도우즈 소켓선언
	int	iError;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {		// 소켓 초기화
		exit(1);
	}


	if ((m_listeningSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {		// 소켓 생성
		printf("fail make socket\n");
		exit(0);
	}

	port = SERV_PORT;
	ZeroMemory(&m_server_addr, sizeof(m_server_addr));		// 초기화
	m_server_addr.sin_family = AF_INET;			// 소켓 옵션 지정
	m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_server_addr.sin_port = htons(port);

	if (bind(m_listeningSock, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr)) < 0) {
		printf("fail bind\n");
		exit(0);
	}

	listen(m_listeningSock, 11);
	m_maxfd = 1;

	Accept();
}

void ChatServer::DisconnectClient(int i)
{
	closesocket(m_client_s[i]);	// i번째 소켓 닫음
	if (i == m_chatuser - 1) {
		m_client_s[i] = m_client_s[m_chatuser - 1];
		m_chatuser--;		// 총유저수 줄임
		printf("Now On the net %d users\n", m_chatuser);
	}
}

/* 현재 채팅 참가자수를 검색 */
int ChatServer::UserNum(int user)
{
	unsigned int max = user;
	int i;

	for (i = 0; i < m_chatuser; i++) {
		if (max < m_client_s[i])
			max = m_client_s[i];
	}

	return max;
}


void ChatServer::Accept()
{
	struct sockaddr_in clientd_addr;
	int clilen;
	SOCKET clientSock;
	int	iError;
	while (1)
	{

		FD_ZERO(&m_read_fds);		// 파일 디스크립터 set 초기화
		FD_SET(m_listeningSock, &m_read_fds);	//listen하고 있는 소켓에 입력이 있는지 검사하기 위해 디스크립터 set에 추가

		for (int i = 0; i < m_chatuser; i++) {
			FD_SET(m_client_s[i], &m_read_fds);
		}

		m_maxfd = UserNum(m_listeningSock) + 1;


		//디스크립터 set 안에서 어느 fd에 입력이 들어왔는지 표시
		if (select(m_maxfd, &m_read_fds, (fd_set *)0, (fd_set *)0, NULL) < 0) {
			iError = WSAGetLastError();
			printf("fail select function\n");
			exit(0);
		}

		if (FD_ISSET(m_listeningSock, &m_read_fds)) {
			// 파일디스크립터에 읽을 데이터가 있으면
			clilen = sizeof(clientd_addr);
			clientSock = accept(m_listeningSock, (struct sockaddr *)&clientd_addr, &clilen);

			if (m_listeningSock == -1) {
				printf("fail accept\n");
				exit(0);
			}

			m_client_s[m_chatuser] = m_listeningSock;
			m_chatuser++;

			send(m_listeningSock, "welcome to black chat", 30, 0);
			printf("%d user connected\n", m_chatuser);
			listen(m_listeningSock, SOMAXCONN);
		}

		//브로드 캐스팅
		for (int i = 0; i < m_chatuser; i++) {		// 접속해 있는 유저수만큼
			char readline[LINE];
			int n;

			memset(readline, '\0', LINE);
			if (FD_ISSET(m_client_s[i], &m_read_fds)) {		// 파일 디스크립터 버퍼 확인
				if ((n = recv(m_client_s[i], readline, LINE, 0)) <= 0) {
					DisconnectClient(i);
					continue;
				}

				if (strstr(readline, "/quit")){		// FIXME : 사용자 삭제를 위한 키워드 처리 수정
					DisconnectClient(i); // 유저 계정 삭제
					continue;
				}

				readline[n] = '\0';
				for (int j = 0; j < m_chatuser; j++) {	// 브로드캐스팅
					send(m_client_s[j], readline, n, 0);
				}
				printf("%s\n", readline);
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
