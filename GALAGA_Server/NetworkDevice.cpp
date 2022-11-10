#include "NetworkDevice.h"

#define BUFSIZE    1024

void CNetworkDevice::SendToNetwork()
{
    // 배열 메세지 종류만큼
    int MessageN[sizeof(MESSAGE_TYPE)];

    // 메세지 타입별로 개수를 배열에 저장
    for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
        MessageN[i] = (int)m_SendTelegrams[i].size();

    int retval;
    // int형 배열을 고정길이 패킷으로 송신(메세지 개수)
    retval = send(m_client_sock, (const char*)MessageN, sizeof(int) * (int)(m_SendTelegrams.size()), 0);
    //if (retval == SOCKET_ERROR) err_display("send() - Message 개수");
    
    int DataSize = 0;

    // 총 크기 - 메세지 개수 * 메세지 크기 <-종류만큼 반복
    for (int i = 0; i < sizeof(MESSAGE_TYPE); i++)
    {
        DataSize += MessageN[i] * MessageSize[i];
    }

    char* Data = new char[DataSize];
    int AddDataSize = 0; // 추가한 데이터 크기

    // Telegram을 하나씩 꺼내서 전달
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

}


void CNetworkDevice::RecvByNetwork()
{
}

Telegram CNetworkDevice::GetTelegram()
{
	return Telegram();
}
