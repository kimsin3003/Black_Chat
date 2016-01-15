#pragma once
#include <WinSock2.h>
class ChatClient
{
public:
	ChatClient(const char* addr);
	~ChatClient();
	void Run();

private:

	void ErrorHandling(char* message);
	void Recieve();
	void StoreCurPosition();
	void GotoBottom();
	void EraseLine();
	void GotoChatLine();
	void Send();

	WSADATA m_wsaData;
	SOCKET m_serversocket;
	SOCKADDR_IN    m_servAddr;
	COORD m_BottonPos;
	COORD m_ChatPos;
	bool printing;
	char id[20];
};

