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

void CLocator::SetPlayer(int playerNum, CPlayer* player)
{
	if (playerNum == 0) {
		Player1 = player;
	}
	else if (playerNum == 1) {
		Player2 = player;
	}
}

CPlayer* CLocator::GetPlayer(int PlayerNum)
{
	if (PlayerNum == 0) {
		return Player1;
	}
	else if (PlayerNum == 1) {
		return Player2;
	}
	return nullptr;
}
