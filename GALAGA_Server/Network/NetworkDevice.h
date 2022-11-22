#pragma once
#include "../Include/Game.h"

class CMessageDispatcher;

class CNetworkDevice
{
private:
	std::array<int, 7> Message_Sizes = {
	28,
	24,
	16,
	20,
	20,
	20,
	16
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

	void CopyTelegramQueue();

	void GetTelegram();
	void AddMessage(Telegram& Message);


	void printTelegram();
};

