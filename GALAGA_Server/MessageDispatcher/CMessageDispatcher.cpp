#include "CMessageDispatcher.h"
#include "..\Object\Object.h"

DEFINITION_SINGLE(CMessageDispatcher);

void CMessageDispatcher::Discharge(CObject* pReceiver, const Telegram& msg)
{
	if (!pReceiver->HandleMessage(msg)) {
		std::cout << "Message Not Handled" << std::endl;
	}
}

void CMessageDispatcher::DispatchMessages(double delay, int sender, int receiver, int msg, void* ExtraInfo)
{
}

