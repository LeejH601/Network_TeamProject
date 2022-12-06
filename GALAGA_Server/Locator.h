#pragma once
#include "Include/Game.h"
#include "Network/NetworkDevice.h"
#include "Object/Player.h"

typedef std::pair<DWORD, CNetworkDevice*> NET_pair;

class comp {
public:
	bool operator()(const NET_pair lhs, const NET_pair rhs) const {
		return lhs.first < rhs.first;
	}
};

class CLocator
{
	std::set< NET_pair, comp> NetworkDevice_list;
	CPlayer* Player1;
	CPlayer* Player2;

public:
	CLocator();
	~CLocator();

	void SetNetworkDevice(DWORD threadID, CNetworkDevice* device);
	void SetNetworkPtrWithHandle(DWORD threadID, CNetworkDevice* device);
	CNetworkDevice* GetNetworkDevice(DWORD threadID);

	void SetPlayer(int playerNum, CPlayer* player);
	CPlayer* GetPlayer(int PlayerNum);
};

extern CLocator Locator;