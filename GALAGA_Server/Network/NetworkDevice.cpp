#include "NetworkDevice.h"
#include "../Core/Timer.h"

CNetworkDevice::CNetworkDevice() 
{
	m_SendTelegrams.resize(7);
	m_RecvTelegrams.resize(7);
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
	int MessageN[7] = { 0 };

	// �޼��� Ÿ�Ժ��� ������ �迭�� ����
	for (int i = 0; i < 7; i++) {
		if (!m_SendTelegrams[i].empty())
			MessageN[i] = (int)m_SendTelegrams[i].size();
	}

	int retval;
	// int�� �迭�� �������� ��Ŷ���� �۽�(�޼��� ����)
	retval = send(m_client_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);

	if (retval == 0)
		return false;
	//if (retval == SOCKET_ERROR) err_display("send() - Message ����");

	int DataSize = 0;

	// �� ũ�� - �޼��� ���� * �޼��� ũ�� <-������ŭ �ݺ�
	for (int i = 0; i < 7; i++)
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
			memcpy(Data + AddDataSize, &m_SendTelegrams[i][j].Receiver, sizeof(int));
			AddDataSize += sizeof(int);
			memcpy(Data + AddDataSize, m_SendTelegrams[i][j].Extrainfo, Message_Sizes[i] - sizeof(int));
			AddDataSize += Message_Sizes[i] - sizeof(int);

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
	std::array<int, 7> nEvents = { 0 };

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

	memcpy(nEvents.data(), buf, nEvents.max_size());

	long remainData = 0;

	for (int i = 0; i < nEvents.max_size(); ++i) {
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

	delete[] dataBuf;
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
			std::cout << "RecvQueue :: " << m_RecvTelegrams[i][j].Msg << " : " << m_RecvTelegrams[i][j].Receiver << " - " << (char*)m_RecvTelegrams[i][j].Extrainfo << std::endl;
		}
	}
}