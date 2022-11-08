#pragma once
#include "Game.h"

class Telegram;



class CNetworkDevice
{
private:
	SOCKET m_client_sock;

	std::vector<std::vector<Telegram>> m_Telegrams;

public:
	void SendToNetwork();
	void RecvByNetwork();

	Telegram GetTelegram();
};

