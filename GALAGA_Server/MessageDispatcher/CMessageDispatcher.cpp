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
	while (!PriorityQ.empty())
	{
		Telegram& telegram = const_cast<Telegram&>(*PriorityQ.begin());

		CObject* pReceiver = CObjectManager::GetInst()->GetObjectFromID(telegram.Receiver);
		if (pReceiver)
			Discharge(pReceiver, telegram);
		PriorityQ.erase(PriorityQ.begin());
	}
}

