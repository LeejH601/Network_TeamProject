#include "NetworkDevice.h"
#include "..\Common.h"

void CNetworkDevice::init(SOCKET sock)
{
	m_client_sock = sock;
}

void CNetworkDevice::SendToNetwork()
{
}

struct metaData {
	int nEvents[7];
	int nTotalSize;
};

void CNetworkDevice::RecvByNetwork()
{
	std::array<int, sizeof(MESSAGE_TYPE)> nEvents;

	int retval;

	char buf[BUFSIZE + 1];


	retval = recv(m_client_sock, buf, nEvents.max_size() * sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		return;
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
			memcpy(telegram.Extrainfo, dataBuf + ReadPointer, Message_Sizes[i] - sizeof(int));
			ReadPointer += Message_Sizes[i] - sizeof(int);

			m_RecvTelegrams[i].push_back(telegram);
		}
	}
}

Telegram CNetworkDevice::GetTelegram()
{
	return Telegram();
}
