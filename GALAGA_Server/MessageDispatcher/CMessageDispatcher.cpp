#include "CMessageDispatcher.h"
#include "..\Object\Object.h"

void CMessageDispatcher::Discharge(CObject* pReceiver, const Telegram& msg)
{
	if (!pReceiver->HandleMessage(msg)) {
		if (msg.Extrainfo)
		{
			std::cout << "Message Not Handled" << std::endl;
		}
	}
}

void CMessageDispatcher::DispatchMessages()
{
	for (const Telegram& tel : PriorityQ)
	{
		Telegram& telegram = const_cast<Telegram&>(tel);

		CObject* pReceiver = CObjectManager::GetInst()->GetObjectFromID(telegram.Receiver);

		if (pReceiver)
			Discharge(pReceiver, telegram);

		if (telegram.Extrainfo)
			delete[] telegram.Extrainfo;
	}
	PriorityQ.clear();
}

