#include "Locator.h"

CLocator::CLocator()
{
}

CLocator::~CLocator()
{
}

void CLocator::SetNetworkDevice(DWORD threadID, CNetworkDevice* device)
{
	NetworkDevice_list.insert(NET_pair(threadID, device));
}

void CLocator::SetNetworkPtrWithHandle(DWORD threadID, CNetworkDevice* device)
{
	auto ptr = NetworkDevice_list.find(NET_pair(threadID, nullptr))->second;
	ptr = device;
}

CNetworkDevice* CLocator::GetNetworkDevice(DWORD threadID)
{
	CNetworkDevice* p = NetworkDevice_list.find(NET_pair(threadID, nullptr))->second;
	
	return p;
}
