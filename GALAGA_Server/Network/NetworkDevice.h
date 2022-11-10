#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "../Include/Game.h"


class CNetworkDevice
{
private:
	std::array<int, 7> Message_Sizes = {
	16,
	12,
	4,
	8,
	8,
	8,
	4
	};


	SOCKET m_client_sock;

	std::vector<std::vector<Telegram>> m_SendTelegrams;
	std::vector<std::vector<Telegram>> m_RecvTelegrams;

public:
	CNetworkDevice();
	~CNetworkDevice();

	void init(SOCKET sock);

	bool SendToNetwork();
	bool RecvByNetwork();

	std::set<Telegram> GetTelegram();
};

