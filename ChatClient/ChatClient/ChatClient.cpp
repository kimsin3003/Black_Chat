#include "stdafx.h"
#include "ChatClient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#define PORT 8787
#define IP     "127.0.0.1"


ChatClient::ChatClient(const char* addr)
{

	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	m_serversocket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_serversocket == INVALID_SOCKET)
		ErrorHandling("hSocket() error");

	memset(&m_servAddr, 0, sizeof(m_servAddr));
	m_servAddr.sin_family = AF_INET;
	m_servAddr.sin_addr.S_un.S_addr = inet_addr(addr);
	m_servAddr.sin_port = htons(PORT);

	if (connect(m_serversocket, (SOCKADDR*)&m_servAddr,
		sizeof(m_servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
		printf("connected to server\n");


	
}

void ChatClient::Run()
{
	std::thread receiver(&ChatClient::Recieve, this);

	std::thread sender(&ChatClient::Send, this);

	receiver.join();
	sender.join();
}


void ChatClient::ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
void ChatClient::Recieve()
{

	int    strLen;
	char message[2048];
	while (true)
	{
		strLen = recv(m_serversocket, message, sizeof(message) - 1, 0);
		if (strLen == -1)
			ErrorHandling("read() error!");
		message[strLen] = 0;
		printf("Message from server : %s \n", message);
	}
}

void ChatClient::Send()
{
	int    strLen;
	char *start = "Now you connected Client\n";

	int addrlen;

	while (true)
	{
		char input[1024];
		gets(input);
		send(m_serversocket, input, strlen(input), 0);
	}
}


ChatClient::~ChatClient()
{
}
