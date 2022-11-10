#include "..\Common.h"
#include "Core.h"

#define SERVERPORT 9000
#define MAXCLIENT 2
char* SERVERIP = (char*)"127.0.0.1";


DWORD WINAPI ProcessClient(LPVOID arg)
{
	
}

bool g_bisPlaying = false;
int g_nPlayClient = 0;

int main(int argc, char* argv[])
{
	int retval;

	if (argc > 1) {
		SERVERIP = argv[1];
	}

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

		HANDLE hThread = CreateThread(NULL, 0, ProcessClient, 0, 0, NULL);

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

			}
			else {
				// 추가적인 초기화 코드 필요
			}
		}
		if (g_bisPlaying)
			CCore::GetInst()->Logic();

	}

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}