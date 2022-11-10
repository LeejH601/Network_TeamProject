#include "NetworkDevice.h"
#include "../Core/Timer.h"

CNetworkDevice::CNetworkDevice() 
{

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
	// �迭 �޼��� ������ŭ
	int MessageN[sizeof(MESSAGE_TYPE)];

	// �޼��� Ÿ�Ժ��� ������ �迭�� ����
	for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
		MessageN[i] = (int)m_SendTelegrams[i].size();

	int retval;
	// int�� �迭�� �������� ��Ŷ���� �۽�(�޼��� ����)
	retval = send(m_client_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);

	if (retval == 0)
		return false;
	//if (retval == SOCKET_ERROR) err_display("send() - Message ����");

	int DataSize = 0;

	// �� ũ�� - �޼��� ���� * �޼��� ũ�� <-������ŭ �ݺ�
	for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
	{
		DataSize += MessageN[i] * Message_Sizes[i];
	}

	char* Data = new char[DataSize];
	int AddDataSize = 0; // �߰��� ������ ũ��

	// Telegram�� �ϳ��� ������ ����
	for (int i = 0; i < m_SendTelegrams.size(); i++)
	{
		for (int j = 0; j < m_SendTelegrams[i].size(); j++)
		{
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].Receiver, sizeof(int));
			AddDataSize += sizeof(int);
			memcpy(Data + AddDataSize, m_SendTelegrams[i][j].Extrainfo, MessageN[i]);
			AddDataSize += MessageN[i];

		}
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
		retval = send(m_client_sock, Data, BufSize, 0);
		//if (retval == SOCKET_ERROR) err_display("send() - ������ ����");
		LeftDataSize -= BufSize;

	}
	delete[] Data;

	return true;
}

bool CNetworkDevice::RecvByNetwork()
{
	std::array<int, sizeof(MESSAGE_TYPE)> nEvents;

	int retval;

	char buf[BUFSIZE + 1];


	retval = recv(m_client_sock, buf, nEvents.max_size() * sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		return false;
	}

	if (retval == 0) {
		return false;
	}

	memcpy(nEvents.data(), buf, nEvents.max_size());

	long remainData = 0;

	for (int i = 0; i < nEvents.max_size(); ++i) {
		remainData += nEvents[i] * Message_Sizes[i];
	}

	char* dataBuf = new char[remainData];
	int cpyLocate = 0;

	while (remainData > 0)
	{
		retval = recv(m_client_sock, buf, BUFSIZE, MSG_WAITALL);
		if (retval == 0)
			break;

		memcpy(dataBuf, buf + cpyLocate, retval);
		cpyLocate += retval;

		remainData -= retval;
	}

	int ReadPointer = 0;
	for (int i = 0; i < nEvents.max_size(); ++i) {
		for (int j = 0; j < nEvents[i]; ++j) {
			Telegram telegram;

			memcpy(&telegram.Receiver, dataBuf + ReadPointer, sizeof(int));
			ReadPointer += sizeof(int);

			telegram.Extrainfo = new char[Message_Sizes[i] - sizeof(int)];
			memcpy(telegram.Extrainfo, dataBuf + ReadPointer, Message_Sizes[i] - sizeof(int));
			ReadPointer += Message_Sizes[i] - sizeof(int);

			telegram.Msg = i;
			telegram.DispatchTime = CTimer::GetInst()->GetTime();

			m_RecvTelegrams[i].push_back(telegram);
		}
	}
}

std::set<Telegram> CNetworkDevice::GetTelegram()
{
	std::set<Telegram> messageQueue;

	for (int i = 0; i < m_RecvTelegrams.size(); ++i) {
		for (int j = 0; j < m_RecvTelegrams[i].size(); ++j) {
			messageQueue.insert(m_RecvTelegrams[i][j]);
		}
		m_RecvTelegrams[i].clear();
	}

	return messageQueue;
}
