#pragma once
#include "Game.h"

class Telegram;



class CNetworkDevice
{
private:
	SOCKET m_client_sock;

	std::vector<std::vector<Telegram>> m_SendTelegrams;
	std::vector<std::vector<Telegram>> m_RecvTelegrams;

public:
	void init(SOCKET sock);

	void SendToNetwork();
	void RecvByNetwork();

	Telegram GetTelegram();
};

