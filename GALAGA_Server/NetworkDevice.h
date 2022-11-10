#pragma once
#include "Game.h"

class Telegram;

int MessageSize[] = {16, 12, 4, 8, 8, 8, 4};

class CNetworkDevice
{
private:
	SOCKET m_client_sock;

	std::vector<std::vector<Telegram>> m_Telegrams;

public:
	void SendToNetwork();
	void RecvByNetwork();

	Telegram GetTelegram();


	std::vector<std::vector<Telegram>> m_SendTelegrams;
	std::vector<std::vector<Telegram>> m_RecvTelegrams;


};

