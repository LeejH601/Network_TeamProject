#include "Locator.h"

CLocator::CLocator()
{
}

CLocator::~CLocator()
{
}

void CLocator::SetNetworkDevice(HANDLE handle, CNetworkDevice* device)
{
	NetworkDevice_list.insert(std::pair<HANDLE, CNetworkDevice*>(handle, device));
}

void CLocator::SetNetworkPtrWithHandle(HANDLE handle, CNetworkDevice* device)
{
	auto ptr = NetworkDevice_list.find(std::pair<HANDLE, CNetworkDevice*>(handle, nullptr))->second;
	ptr = device;
}

CNetworkDevice* CLocator::GetNetworkDevice(HANDLE handle)
{
	return NetworkDevice_list.find(std::pair<HANDLE, CNetworkDevice*>(handle, nullptr))->second;
}
