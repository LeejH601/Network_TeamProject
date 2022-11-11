#pragma once
#include "..\Include\Game.h"

class CObject;
class CMessageDispatcher
{
public:
    DECLARE_MYSINGLE(CMessageDispatcher);
private:
    std::set<Telegram> PriorityQ;

    void Discharge(CObject* pReceiver, const Telegram& msg);

public:

    std::set<Telegram>& GetMessageQueue() { return PriorityQ; };
public:
    void DispatchMessages();
};

