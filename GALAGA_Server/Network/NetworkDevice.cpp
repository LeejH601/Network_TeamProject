#include "NetworkDevice.h"
#include "../Core/Timer.h"
#include "../MessageDispatcher/CMessageDispatcher.h"
#include "..\CLocator.h"


CNetworkDevice::CNetworkDevice() 
{
	m_SendTelegrams.resize((int)MESSAGE_TYPE::END_Enum);
	m_RecvTelegrams.resize((int)MESSAGE_TYPE::END_Enum);
}

CNetworkDevice::~CNetworkDevice() 
{
	if (m_client_sock)
		closesocket(m_client_sock);

}

void CNetworkDevice::init(SOCKET sock)
{
	m_client_sock = sock;
}

bool CNetworkDevice::SendToNetwork()
{
	// 배열 메세지 종류만큼
	int MessageN[(int)MESSAGE_TYPE::END_Enum] = { 0 };

	// 메세지 타입별로 개수를 배열에 저장
	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; i++) {
		if (!m_SendTelegrams[i].empty())
			MessageN[i] = (int)m_SendTelegrams[i].size();
	}

	int retval;
	// int형 배열을 고정길이 패킷으로 송신(메세지 개수)
	retval = send(m_client_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);

	if (retval == 0)
		return false;
	//if (retval == SOCKET_ERROR) err_display("send() - Message 개수");

	int DataSize = 0;

	// 총 크기 - 메세지 개수 * 메세지 크기 <-종류만큼 반복
	for (int i = 0; i < (int)MESSAGE_TYPE::END_Enum; i++)
	{
		DataSize += MessageN[i] * Message_Sizes[i];
	}

	if (DataSize == 0)
		return false;
	char* Data = new char[DataSize];
	int AddDataSize = 0; // 추가한 데이터 크기

	// Telegram을 하나씩 꺼내서 전달
	for (int i = 0; i < m_SendTelegrams.size(); i++)
	{
		for (int j = 0; j < m_SendTelegrams[i].size(); j++)
		{
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].Receiver, sizeof(int));
			AddDataSize += sizeof(int);
			memcpy(Data + AddDataSize, m_SendTelegrams[i][j].Extrainfo, Message_Sizes[i] - sizeof(int));
			AddDataSize += Message_Sizes[i] - sizeof(int);

		}
	}

	// 데이터를 AddDataSize(저장된 데이터 크기)만큼 전달
	int LeftDataSize = AddDataSize; // 미수신 데이터 크기
	int BufSize = BUFSIZE;
	while (LeftDataSize > 0)
	{
		if (LeftDataSize < BUFSIZE)
			BufSize = LeftDataSize;
		else
			BufSize = BUFSIZE;

		// 데이터 보내기 (가변 길이) - 데이터 내용
		retval = send(m_client_sock, Data, BufSize, 0);
		//if (retval == SOCKET_ERROR) err_display("send() - 데이터 내용");
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


	retval = recv(m_client_sock, buf, 28, MSG_WAITALL);
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
		retval = recv(m_client_sock, buf, BUFSIZE, 0);
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

			memcpy(&telegram.Receiver, dataBuf + ReadPointer, sizeof(int));
			ReadPointer += sizeof(int);

			if (Message_Sizes[i] - sizeof(int)) {
				telegram.Extrainfo = new char[Message_Sizes[i] - sizeof(int)];
				memcpy(telegram.Extrainfo, dataBuf + ReadPointer, Message_Sizes[i] - sizeof(int));
				ReadPointer += Message_Sizes[i] - sizeof(int);
			}

			telegram.Msg = i;
			telegram.DispatchTime = CTimer::GetInst()->GetTime();

			m_RecvTelegrams[i].push_back(telegram);
		}
	}

	delete[] dataBuf;
}

void CNetworkDevice::CopyTelegramQueue()
{
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < m_RecvTelegrams[i].size(); ++i) {
			m_SendTelegrams[i].push_back(m_RecvTelegrams[i][j]);
		}
	}
}

void CNetworkDevice::GetTelegram()
{
	std::set<Telegram> MessageQueue = Locator.GetMessageDispathcer()->GetMessageQueue();
	//std::set<Telegram> MessageQueue = CMessageDispatcher::GetInst()->GetMessageQueue();

	for (int i = 0; i < m_RecvTelegrams.size(); ++i) {
		for (int j = 0; j < m_RecvTelegrams[i].size(); ++j) {
			MessageQueue.insert(m_RecvTelegrams[i][j]);
		}
		m_RecvTelegrams[i].clear();
	}
}

void CNetworkDevice::printTelegram()
{
	for (int i = 0; i < m_SendTelegrams.size(); i++)
	{
		for (int j = 0; j < m_SendTelegrams[i].size(); j++)
		{
			std::cout << "SendQueue :: " << m_SendTelegrams[i][j].Msg << " : " << m_SendTelegrams[i][j].Receiver << " - " << (char*)m_SendTelegrams[i][j].Extrainfo << std::endl;
		}
	}
	for (int i = 0; i < m_RecvTelegrams.size(); i++)
	{
		for (int j = 0; j < m_RecvTelegrams[i].size(); j++)
		{
			if( m_RecvTelegrams[i][j].Extrainfo)
				std::cout << "RecvQueue :: " << m_RecvTelegrams[i][j].Msg << " : " << m_RecvTelegrams[i][j].Receiver << " - " << (char*)m_RecvTelegrams[i][j].Extrainfo << std::endl;
			else
				std::cout << "RecvQueue :: " << m_RecvTelegrams[i][j].Msg << " : " << m_RecvTelegrams[i][j].Receiver << " - " << "nullptr" << std::endl;
		}
	}
}
