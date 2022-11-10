#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "../Include/Game.h"

std::array<int, 7> Message_Sizes = {
	16,
	12,
	4,
	8,
	8,
	8,
	4
};

class CNetworkDevice
{
private:
	SOCKET m_client_sock;

	std::vector<std::vector<Telegram>> m_SendTelegrams;
	std::vector<std::vector<Telegram>> m_RecvTelegrams;

public:
	void SendToNetwork();
	void RecvByNetwork();

	std::set<Telegram> GetTelegram();
};

