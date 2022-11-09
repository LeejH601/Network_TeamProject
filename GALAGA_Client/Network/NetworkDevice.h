#pragma once
#include "../Include/Game.h"

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