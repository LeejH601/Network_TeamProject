#pragma once
#include "Include/Game.h"
#include "Network/NetworkDevice.h"

typedef std::pair<HANDLE, CNetworkDevice*> NET_pair;

class comp {
public:
	bool operator()(const NET_pair lhs, const NET_pair rhs) const {
		return lhs.first < rhs.first;
	}
};

class CLocator
{
	std::set<std::pair<HANDLE, CNetworkDevice*>, comp> NetworkDevice_list;

public:
	CLocator();
	~CLocator();

	void SetNetworkDevice(HANDLE handle, CNetworkDevice* device);
	void SetNetworkPtrWithHandle(HANDLE handle, CNetworkDevice* device);
	CNetworkDevice* GetNetworkDevice(HANDLE handle);
};

extern CLocator Locator;