#include "CMessageDispatcher.h"
#include "..\Object\Object.h"

void CMessageDispatcher::Discharge(CObject* pReceiver, const Telegram& msg)
{
	if (!pReceiver->HandleMessage(msg)) {
		std::cout << "Message Not Handled" << std::endl;
	}
}

void CMessageDispatcher::DispatchMessages()
{
	while (!PriorityQ.empty())
	{
		const Telegram& telegram = *PriorityQ.begin();

		CObject* pReceiver = CObjectManager::GetInst()->GetObjectFromID(telegram.Receiver);
		Discharge(pReceiver, telegram);

		PriorityQ.erase(PriorityQ.begin());
	}
}

