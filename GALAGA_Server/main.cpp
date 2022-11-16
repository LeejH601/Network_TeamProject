#include "..\Common.h"
#include "Core.h"
#include "Network/NetworkDevice.h"
#include "MessageDispatcher/CMessageDispatcher.h"
#include "Locator.h"

#define SERVERPORT 9000
#define MAXCLIENT 2
char* SERVERIP = (char*)"127.0.0.1";

CRITICAL_SECTION cs;
std::vector<CRITICAL_SECTION> client_cs;
CRITICAL_SECTION main_loop_cs;

CLocator Locator;

struct ThreadArgument {
	SOCKET sock;
	CRITICAL_SECTION* pcs;
};

DWORD WINAPI ProcessGameLoop(LPVOID arg)
{
	HANDLE hThread = arg;

	// ������ �ʱ�ȭ �մϴ�. 
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	CCore::GetInst()->Run();
}

bool g_bisPlaying = false;
int g_nPlayClient = 0;

DWORD WINAPI ProcessClient(LPVOID arg)
{
	ThreadArgument Arg;
	memcpy(&Arg, arg, sizeof(ThreadArgument));

	CRITICAL_SECTION* pCs = Arg.pcs;
	CNetworkDevice Network_Device;
	Network_Device.init((SOCKET)Arg.sock);
	Locator.SetNetworkDevice(GetCurrentThreadId(), &Network_Device);
	auto test = Locator.GetNetworkDevice(GetCurrentThreadId());
	CCore::GetInst()->SetPlayerHandle(GetCurrentThreadId(), g_nPlayClient - 1);

	int iTimeout = 1000;
	setsockopt(Arg.sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&iTimeout, sizeof(iTimeout));
	DWORD optval = 1;
	setsockopt(Arg.sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, sizeof(optval));
	std::cout << "connect client" << std::endl;

	while (true)
	{
		std::cout << "??????????" << std::endl;
		EnterCriticalSection(pCs);
		if (Network_Device.RecvByNetwork());
		LeaveCriticalSection(pCs);

		/*EnterCriticalSection(pCs);
		Network_Device.CopyTelegramQueue();
		LeaveCriticalSection(pCs);*/

		EnterCriticalSection(pCs);
		Network_Device.GetTelegram();
		LeaveCriticalSection(pCs);

		EnterCriticalSection(pCs);
		if (Network_Device.SendToNetwork());
		LeaveCriticalSection(pCs);

		EnterCriticalSection(pCs);
		Network_Device.printTelegram();
		LeaveCriticalSection(pCs);
	}

	return 0;
}



int main(int argc, char* argv[])
{
	int retval;
	client_cs.push_back(CRITICAL_SECTION());
	client_cs.push_back(CRITICAL_SECTION());

	if (argc > 1) {
		SERVERIP = argv[1];
	}

	InitializeCriticalSection(&cs);
	for (CRITICAL_SECTION& _cs : client_cs) {
		InitializeCriticalSection(&_cs);
	}
	InitializeCriticalSection(&main_loop_cs);


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

		ThreadArgument arg;
		arg.sock = client_sock;
		arg.pcs = &client_cs[g_nPlayClient];

		HANDLE hThread = CreateThread(NULL, 0, ProcessClient, &arg, 0, NULL);

		if (hThread == NULL || g_nPlayClient >= MAXCLIENT) { closesocket(client_sock); }

		else {
			g_nPlayClient++;

			if (!g_bisPlaying) {
				HANDLE hGameThread = CreateThread(NULL, 0, ProcessGameLoop, &hThread, 0, NULL);
				g_bisPlaying = true;
				CloseHandle(hGameThread);
			}
			else {
				// �߰����� �ʱ�ȭ �ڵ� �ʿ�
				//CCore::GetInst()->SetPlayerHandle(hThread, 1);
			}

			CloseHandle(hThread);
		}
	}

	DeleteCriticalSection(&cs);

	for (CRITICAL_SECTION& _cs : client_cs) {
		DeleteCriticalSection(&_cs);
	}
	DeleteCriticalSection(&main_loop_cs);

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}