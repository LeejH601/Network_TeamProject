#pragma once
#include "Include/Game.h"
#include "Network/NetworkDevice.h"

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

public:
	CLocator();
	~CLocator();

	void SetNetworkDevice(DWORD threadID, CNetworkDevice* device);
	void SetNetworkPtrWithHandle(DWORD threadID, CNetworkDevice* device);
	CNetworkDevice* GetNetworkDevice(DWORD threadID);
};

extern CLocator Locator;