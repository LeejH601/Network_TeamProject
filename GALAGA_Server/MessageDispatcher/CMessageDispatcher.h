#pragma once
#include "..\Include\Game.h"

class CObject;

class CMessageDispatcher
{

private:
    std::set<Telegram> PriorityQ;

    void Discharge(CObject* pReceiver, const Telegram& msg);

public:

    std::set<Telegram>& GetMessageQueue() { return PriorityQ; };

public:
    void DispatchMessages(double  delay,
        int    sender,
        int    receiver,
        int    msg,
        void* ExtraInfo);


};

