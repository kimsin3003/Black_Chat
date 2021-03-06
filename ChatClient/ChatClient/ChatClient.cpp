#include "stdafx.h"
#include "ChatClient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#define PORT 8787

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

ChatClient::ChatClient(const char* addr)
{

	m_BottonPos.X = 0;
	m_BottonPos.Y = 19;
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	m_serversocket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_serversocket == INVALID_SOCKET)
		ErrorHandling("hSocket() error");

	memset(&m_servAddr, 0, sizeof(m_servAddr));
	m_servAddr.sin_family = AF_INET;
	m_servAddr.sin_addr.S_un.S_addr = inet_addr(addr);
	m_servAddr.sin_port = htons(PORT);

	std::cout << "id: ";
	std::cin >> id;

	system("cls");

	if (connect(m_serversocket, (SOCKADDR*)&m_servAddr,
		sizeof(m_servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
		printf("connected to server\n");

	send(m_serversocket, id, strlen(id), 0);
	StoreCurPosition();
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

	int    idLen, strLen;
	char id[30];
	char message[125];
	while (true)
	{
		idLen = recv(m_serversocket, id, 30 - 1, 0);
		strLen = recv(m_serversocket, message, sizeof(message) - 1, 0);
		if (idLen == -1 || strLen == -1)
			ErrorHandling("read() error!");
		id[idLen] = 0;
		message[strLen] = 0;

		printing = true;
		GotoChatLine();
		printf("%s : %s \n", id, message);
		StoreCurPosition();
		printing = false;
	}
}

void ChatClient::StoreCurPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hcon != INVALID_HANDLE_VALUE &&	GetConsoleScreenBufferInfo(hcon, &con))
	{
		m_ChatPos = con.dwCursorPosition;
	}
}

void ChatClient::GotoBottom()
{
	gotoxy(m_BottonPos.X, m_BottonPos.Y);
}

void ChatClient::EraseLine()
{
	std::cout << "                                                     " ;
}

void ChatClient::GotoChatLine()
{
	gotoxy(m_BottonPos.X, m_BottonPos.Y - 19);
}

void ChatClient::Send()
{
	int    strLen;
	char *start = "Now you connected Client\n";

	int addrlen;

	while (true)
	{
		if (printing)
			continue;
		char input[1024];
		GotoBottom();
		EraseLine();
		GotoBottom();
		printf("Message: ");
		std::cin >> input;
		POINT curPos;


		send(m_serversocket, input, strlen(input), 0);
	}
}


ChatClient::~ChatClient()
{
}
