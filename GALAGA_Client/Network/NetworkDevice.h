#pragma once
#include "../Game.h"

class CNetworkDevice
{
private:
	SOCKET sock;
public:
	DECLARE_SINGLE(CNetworkDevice);
public:
	bool Init();
public:
	void SendToNetwork();
	void RecvByNetwork();
};