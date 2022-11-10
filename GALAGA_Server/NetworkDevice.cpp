#include "NetworkDevice.h"

#define BUFSIZE    1024

void CNetworkDevice::SendToNetwork()
{
    // �迭 �޼��� ������ŭ
    int MessageN[sizeof(MESSAGE_TYPE)];

    // �޼��� Ÿ�Ժ��� ������ �迭�� ����
    for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
        MessageN[i] = (int)m_SendTelegrams[i].size();

    int retval;
    // int�� �迭�� �������� ��Ŷ���� �۽�(�޼��� ����)
    retval = send(m_client_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);
    //if (retval == SOCKET_ERROR) err_display("send() - Message ����");
    
    int DataSize = 0;

    // �� ũ�� - �޼��� ���� * �޼��� ũ�� <-������ŭ �ݺ�
    for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
    {
        DataSize += MessageN[i] * MessageSize[i];
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

}


void CNetworkDevice::RecvByNetwork()
{
}

Telegram CNetworkDevice::GetTelegram()
{
	return Telegram();
}
