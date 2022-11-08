#include "NetworkDevice.h"

DEFINITION_SINGLE(CNetworkDevice);

CNetworkDevice::CNetworkDevice()
{
}

CNetworkDevice::~CNetworkDevice()
{
	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
}

bool CNetworkDevice::Init()
{
	// ��Ʈ��ũ ���� �ʱ�ȭ
	char* SERVERIP;
	u_short SERVERPORT;
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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
