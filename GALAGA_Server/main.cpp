#include "..\Common.h"
#include "Core.h"
#include "Network/NetworkDevice.h"
#include "MessageDispatcher/CMessageDispatcher.h"

#define SERVERPORT 9000
#define MAXCLIENT 2
char* SERVERIP = (char*)"127.0.0.1";

CRITICAL_SECTION cs;

DWORD WINAPI ProcessClient(LPVOID arg)
{
	CNetworkDevice Network_Device;
	Network_Device.init((SOCKET)arg);

	std::cout << "connect client" << std::endl;

	while (true)
	{
		EnterCriticalSection(&cs);
		if (Network_Device.RecvByNetwork());
		LeaveCriticalSection(&cs);

		EnterCriticalSection(&cs);
		Network_Device.CopyTelegramQueue();
		LeaveCriticalSection(&cs);

		EnterCriticalSection(&cs);
		Network_Device.GetTelegram();
		LeaveCriticalSection(&cs);

		EnterCriticalSection(&cs);
		if (Network_Device.SendToNetwork());
		LeaveCriticalSection(&cs);

		EnterCriticalSection(&cs);
		Network_Device.printTelegram();
		LeaveCriticalSection(&cs);
	}

	return 0;
}

bool g_bisPlaying = false;
int g_nPlayClient = 0;

int main(int argc, char* argv[])
{
	int retval;

	if (argc > 1) {
		SERVERIP = argv[1];
	}

	InitializeCriticalSection(&cs);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);

	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	int len;
	char buf[BUFSIZE + 1];

	while (true)
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		HANDLE hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL);

		if (hThread == NULL || g_nPlayClient >= MAXCLIENT) { closesocket(client_sock); }

		else {
			g_nPlayClient++;
			CloseHandle(hThread);

			if (!g_bisPlaying) {
				// 게임을 초기화 합니다. 
				if (!CCore::GetInst()->Init())
				{
					CCore::DestroyInst();
					return 0;
				}

				g_bisPlaying = true;
			}
			else {
				// 추가적인 초기화 코드 필요
			}
		}
		if (g_bisPlaying)
			CCore::GetInst()->Logic();

	}

	DeleteCriticalSection(&cs);

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}