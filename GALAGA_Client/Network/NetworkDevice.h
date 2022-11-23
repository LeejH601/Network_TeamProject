#pragma once
#include "../Include/Game.h"

class CNetworkDevice
{
public:
	DECLARE_SINGLE(CNetworkDevice);
private:
	std::array<int, 7> Message_Sizes = {
	20, // -> Object Enum �߰� (4byte) ����: 16
	12,
	4,
	8,
	8,
	8,
	4
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