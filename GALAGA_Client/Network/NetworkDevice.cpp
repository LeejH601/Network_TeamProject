#include "NetworkDevice.h"

DEFINITION_SINGLE(CNetworkDevice);

CNetworkDevice::CNetworkDevice()
{
}

CNetworkDevice::~CNetworkDevice()
{
}

bool CNetworkDevice::Init()
{
	// 네트워크 소켓 초기화
	return true;
}