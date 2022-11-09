#pragma once
#include "../Game.h"

class CNetworkDevice
{
public:
	DECLARE_SINGLE(CNetworkDevice);
public:
	bool Init();
public:
	void SendToNetwork();
	void RecvByNetwork();
};