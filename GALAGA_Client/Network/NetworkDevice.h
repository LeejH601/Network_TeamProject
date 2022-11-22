#pragma once
#include "../Include/Game.h"

class CNetworkDevice
{
public:
	DECLARE_SINGLE(CNetworkDevice);
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
	SOCKET m_sock;

	std::vector<std::vector<Telegram>> m_SendTelegrams;
	std::vector<std::vector<Telegram>> m_RecvTelegrams;
public:
	bool Init();
	void init(SOCKET sock);
	void AddMessage(Telegram& Message);
	bool SendToNetwork();
	bool RecvByNetwork();
	void GetTelegram();
};