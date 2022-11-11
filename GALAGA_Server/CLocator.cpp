#include "CLocator.h"

CLocator::CLocator()
{
}

CLocator::~CLocator()
{
    if (MessageDispatcher)
        delete MessageDispatcher;
}

void CLocator::SetMessageDispatcher(CMessageDispatcher* dispatcher)
{
    MessageDispatcher = dispatcher;
}

CMessageDispatcher* CLocator::GetMessageDispathcer()
{
    return MessageDispatcher;
}
