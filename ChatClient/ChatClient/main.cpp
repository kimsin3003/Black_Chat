// ChatClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<thread>
#include "ChatClient.h"

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#define PORT 8787
#define IP     "127.0.0.1"

void ErrorHandling(char* message);

int _tmain(int argc, char** argv)
{

	ChatClient cc(IP);
	cc.Run();
// 	WSADATA wsaData;
// 	SOCKET hSocket;
// 	char message[30];
// 	int    strLen;
// 	SOCKADDR_IN    servAddr;
// 
// 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
// 		ErrorHandling("WSAStartup() error!");
// 
// 	hSocket = socket(PF_INET, SOCK_STREAM, 0);
// 	if (hSocket == INVALID_SOCKET)
// 		ErrorHandling("hSocket() error");
// 
// 	memset(&servAddr, 0, sizeof(servAddr));
// 	servAddr.sin_family = AF_INET;
// 	servAddr.sin_addr.S_un.S_addr = inet_addr(IP);
// 	servAddr.sin_port = htons(PORT);
// 
// 	if (connect(hSocket, (SOCKADDR*)&servAddr,
// 		sizeof(servAddr)) == SOCKET_ERROR)
// 		ErrorHandling("connect() error!");
// 
// 
// 	std::thread receiver()
// 	/*
// 	윈도우는 소켓을 파일로 보지 않기 때문에 read,write 같은 파일 입출력 함수가 아닌
// 	recv, send 함수를 사용한다.
// 	int recv(SOCKET s, char* buf, int len, int flags);
// 	int send(SOCKET s, char* buf, int len, int flags);
// 	*/
// 
// 	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
// 	if (strLen == -1)
// 		ErrorHandling("read() error!");
// 	message[strLen] = 0;
// 	printf("Message from server : %s \n", message);
// 
// 	closesocket(hSocket);
// 	WSACleanup();
	return 0;

}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}