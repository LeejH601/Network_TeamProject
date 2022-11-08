#include "NetworkDevice.h"

DEFINITION_SINGLE(CNetworkDevice);

CNetworkDevice::CNetworkDevice()
{
}

CNetworkDevice::~CNetworkDevice()
{
	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
}

bool CNetworkDevice::Init()
{
	// 네트워크 소켓 초기화
	char* SERVERIP;
	u_short SERVERPORT;
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);

	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	return true;
}

void CNetworkDevice::SendToNetwork()
{
}

void CNetworkDevice::RecvByNetwork()
{
}
