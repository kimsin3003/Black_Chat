// ChatServer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ChatServer.h"
// #include <WinSock2.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #define  _WINSOCK_DEPRECATED_NO_WARNINGS
// #pragma comment(lib, "Ws2_32.lib")
// 
// #define LINE		1024
// #define MAXCLIENT	5
// #define	SERV_PORT	8787
// 
// int maxfdp1;
// int chatuser;	// ä�� ������ ��
// unsigned int client_s[MAXCLIENT];
// char *escape = "/quit";	// ���� ���

// /* i��° ���� �������� */
// void disconCli(int i)
// {
// 	closesocket(client_s[i]);	// i��° ���� ����
// 	if (i == chatuser-1) {
// 		client_s[i] = client_s[chatuser-1];
// 		chatuser--;		// �������� ����
// 		printf("Now On the net %d users\n", chatuser);
// 	}
// }
// 
// /* ���� ä�� �����ڼ��� �˻� */
// int maxuser(int user)
// {
// 	unsigned int max = user;
// 	int i;
// 	
// 	for (i = 0; i < chatuser; i++) {
// 		if (max < client_s[i])
// 			max = client_s[i];
// 	}
// 
// 	return max;
// }

int _tmain(int argc, char** argv)
{
	ChatServer cs;
	cs.Start();

// 	char readline[LINE];	// read buffer
// 	char *start = "Now you connected Server\n";		// ���Ӿ˸�
// 	int	i,j,n, addrlen;
// 	SOCKET clientsocket, clilen;		// ���� ����
// 	unsigned short	port;
// 	fd_set read_fds;
// 	struct sockaddr_in clientd_addr, server_addr;	// ���� �ּ�
// 	WSADATA wsa;		// �������� ���ϼ���
// 	int	iError;
// 	
// 	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {		// ���� �ʱ�ȭ
// 		exit(1);
// 	}
// 
// 
// 	if ((clientsocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {		// ���� ����
// 		printf("fail make socket\n");
// 		exit(0);
// 	}
// 	
// 	port = SERV_PORT;
// 	ZeroMemory(&server_addr, sizeof(server_addr));		// �ʱ�ȭ
// 	server_addr.sin_family = AF_INET;			// ���� �ɼ� ����
// 	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
// 	server_addr.sin_port = htons(port);
// 
// 	if (bind(clientsocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
// 		printf("fail bind\n");
// 		exit(0);
// 	}
// 
// 	listen(clientsocket, SOMAXCONN);	// ���� ���, SOMAXCONN : �ִ� �����
// 	maxfdp1 = clientsocket + 1;			// �ִ���� + 1
// 
// // 	while (1)
// // 	{
// // 
// // 		addrlen = sizeof(clientd_addr); // �ּұ��� ����
// // 		// ���� ����
// // 		clilen = sizeof(clientd_addr);
// // 		clientsocket = accept(serversocket, (struct sockaddr *)&clientd_addr, &addrlen);
// // 		printf("%d user connected\n", chatuser);
// // 		send(clientsocket, "fuck you", strlen("fuck you"), 0);
// // 	}
// 
// 	while(1)
// 	{
// 		FD_ZERO(&read_fds);		// ���� ��ũ���� �ʱ�ȭ
// 		FD_SET(clientsocket, &read_fds);
// 		for (i = 0; i < chatuser; i++) {
// 			FD_SET(client_s[i], &read_fds);
// 		}
// 		maxfdp1 = maxuser(clientsocket)+1;
// 
// 		if (select(maxfdp1,&read_fds,(fd_set *)0, (fd_set *)0, NULL) < 0) {
// 			iError = WSAGetLastError();
// 			printf("fail select function\n");
// 			exit(0);
// 		}
// 
// 		if (FD_ISSET(clientsocket, &read_fds)) {
// 			// ���ϵ�ũ���Ϳ� ���� �����Ͱ� ������
// 			addrlen = sizeof(clientd_addr); // �ּұ��� ����
// 			// ���� ����
// 			clilen = sizeof(clientd_addr);
// 			clientsocket = accept(clientsocket, (struct sockaddr *)&clientd_addr, &addrlen);
// 
// 			if (clientsocket == -1) {
// 				printf("fail accept\n");
// 				exit(0);
// 			}
// 			
// 			client_s[chatuser] = clientsocket;
// 			chatuser++;
// 
// 			send(clientsocket, start, strlen(start), 0);
// 			printf("%d user connected\n", chatuser);		// �������Ӿ˸�
// 		}
// 
// 		// ��ε� ĳ����
// 		for (i = 0; i < chatuser; i++) {		// ������ �ִ� ��������ŭ
// 			memset(readline, '\0', LINE);
// 			if (FD_ISSET(client_s[i], &read_fds)) {		// ���� ��ũ���� ���� Ȯ��
// 				if ((n = recv(client_s[i], readline, LINE, 0)) <= 0) {
// 					disconCli(i);
// 					continue;
// 				}
// 
// 				if (strstr(readline, escape)){		// FIXME : ����� ������ ���� Ű���� ó�� ����
// 					disconCli(i); // ���� ���� ����
// 					continue;
// 				}
// 
// 				readline[n] = '\0';
// 				for (j = 0; j < chatuser; j++) {	// ��ε�ĳ����
// 					send(client_s[j], readline, n, 0);
// 				}
// 				printf("%s\n", readline);
// 			}
// 		}
// 	}
// 	closesocket(clientsocket);
// 	WSACleanup();
	return 0;
} 