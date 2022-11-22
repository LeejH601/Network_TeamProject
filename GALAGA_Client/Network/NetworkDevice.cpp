#include "../Core/Timer.h"
#include "NetworkDevice.h"
#include "../MessageDispatcher/CMessageDispatcher.h"

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

DEFINITION_SINGLE(CNetworkDevice);

CNetworkDevice::CNetworkDevice()
{
	m_SendTelegrams.resize(7);
	m_RecvTelegrams.resize(7);
}

CNetworkDevice::~CNetworkDevice()
{
	// 소켓 닫기
	closesocket(m_sock);

	// 윈속 종료
	WSACleanup();
}

bool CNetworkDevice::Init()
{
	int retval = 0;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);

	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(m_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	return true;
}

void CNetworkDevice::init(SOCKET sock)
{
}

bool CNetworkDevice::SendToNetwork()
{
	// �迭 �޼��� ������ŭ
	int MessageN[(int)MESSAGE_TYPE::END_Enum] = { 0 };

	// �޼��� Ÿ�Ժ��� ������ �迭�� ����
	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; i++) {
		if (!m_SendTelegrams[i].empty())
			MessageN[i] = (int)m_SendTelegrams[i].size();
	}

	int retval;
	// int�� �迭�� �������� ��Ŷ���� �۽�(�޼��� ����)
	retval = send(m_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);

	if (retval == 0)
		return false;
	//if (retval == SOCKET_ERROR) err_display("send() - Message ����");

	int DataSize = 0;

	// �� ũ�� - �޼��� ���� * �޼��� ũ�� <-������ŭ �ݺ�
	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; i++)
	{
		DataSize += MessageN[i] * Message_Sizes[i];
	}

	if (DataSize == 0)
		return false;
	char* Data = new char[DataSize];
	int AddDataSize = 0; // �߰��� ������ ũ��

	// Telegram�� �ϳ��� ������ ����
	for (int i = 0; i < m_SendTelegrams.size(); i++)
	{
		for (int j = 0; j < m_SendTelegrams[i].size(); j++)
		{
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].Sender, sizeof(int));
			AddDataSize += sizeof(int);
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].DispatchTime, sizeof(LONGLONG));
			AddDataSize += sizeof(LONGLONG);
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].Receiver, sizeof(int));
			AddDataSize += sizeof(int);
			if (m_SendTelegrams[i][j].Extrainfo)
			{
				memcpy(Data + AddDataSize, m_SendTelegrams[i][j].Extrainfo, Message_Sizes[i] - (sizeof(int) + sizeof(LONGLONG) + sizeof(int)));
				AddDataSize += Message_Sizes[i] - (sizeof(int) + sizeof(LONGLONG) + sizeof(int));
				delete m_SendTelegrams[i][j].Extrainfo;
			}
		}
		m_SendTelegrams[i].clear();
	}

	// �����͸� AddDataSize(����� ������ ũ��)��ŭ ����
	int LeftDataSize = AddDataSize; // �̼��� ������ ũ��
	int BufSize = BUFSIZE;
	while (LeftDataSize > 0)
	{
		if (LeftDataSize < BUFSIZE)
			BufSize = LeftDataSize;
		else
			BufSize = BUFSIZE;

		// ������ ������ (���� ����) - ������ ����
		retval = send(m_sock, Data, BufSize, 0);
		//if (retval == SOCKET_ERROR) err_display("send() - ������ ����");
		LeftDataSize -= BufSize;

	}
	delete[] Data;

	return true;
}

bool CNetworkDevice::RecvByNetwork()
{
	std::array<int, (int)MESSAGE_TYPE::END_Enum> nEvents = { 0 };

	int retval;

	char buf[BUFSIZE + 1];
	ZeroMemory(buf, sizeof(buf));


	retval = recv(m_sock, buf, 28, MSG_WAITALL);
	//retval = recv(m_client_sock, buf, nEvents.max_size() * sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		return false;
	}

	if (retval == 0) {
		return false;
	}

	memcpy(nEvents.data(), buf, nEvents.max_size() * sizeof(int));

	long remainData = 0;

	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; ++i) {
		remainData += nEvents[i] * Message_Sizes[i];
	}

	char* dataBuf = new char[remainData];
	int cpyLocate = 0;

	while (remainData > 0)
	{
		retval = recv(m_sock, buf, BUFSIZE, 0);
		if (retval == 0)
			break;

		memcpy(dataBuf, buf + cpyLocate, retval);
		cpyLocate += retval;

		remainData -= retval;
	}

	int ReadPointer = 0;
	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; ++i) {
		for (int j = 0; j < nEvents[i]; ++j) {
			Telegram telegram;
			memcpy(&telegram.Sender, dataBuf + ReadPointer, sizeof(int));
			ReadPointer += sizeof(int);

			memcpy(&telegram.DispatchTime, dataBuf + ReadPointer, sizeof(LONGLONG));
			ReadPointer += sizeof(LONGLONG);

			memcpy(&telegram.Receiver, dataBuf + ReadPointer, sizeof(int));
			ReadPointer += sizeof(int);

			if (Message_Sizes[i] - sizeof(int))
			{
				telegram.Extrainfo = new char[Message_Sizes[i] - sizeof(int)];
				memcpy(telegram.Extrainfo, dataBuf + ReadPointer, Message_Sizes[i] - (sizeof(int) + sizeof(int) + sizeof(LONGLONG)));
				ReadPointer += Message_Sizes[i] - sizeof(int);
			}

			telegram.Msg = i;
			telegram.DispatchTime = CTimer::GetInst()->GetTime();

			m_RecvTelegrams[i].push_back(telegram);
		}
	}

	GetTelegram();

	delete[] dataBuf;
}

void CNetworkDevice::AddMessage(Telegram& Message)
{
	Telegram messageQueue = Message;
	if (messageQueue.Extrainfo)
	{
		messageQueue.Extrainfo = new char[Message_Sizes[Message.Msg] - sizeof(int)];
		memcpy(messageQueue.Extrainfo, Message.Extrainfo, Message_Sizes[Message.Msg] - sizeof(int));
	}

	m_SendTelegrams[Message.Msg].push_back(messageQueue);
}

void CNetworkDevice::GetTelegram()
{
	std::set<Telegram>* MessageQueue = CMessageDispatcher::GetInst()->GetMessageQueue();

	for (int i = 0; i < m_RecvTelegrams.size(); ++i) {
		for (int j = 0; j < m_RecvTelegrams[i].size(); ++j) {
			MessageQueue->insert(m_RecvTelegrams[i][j]);
		}
		m_RecvTelegrams[i].clear();
	}
}