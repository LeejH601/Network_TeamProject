#pragma once
#include "Include/Game.h"
#include "MessageDispatcher/CMessageDispatcher.h"

class CLocator
{
	CMessageDispatcher* MessageDispatcher;

public:
	CLocator();
	~CLocator();

	void SetMessageDispatcher(CMessageDispatcher* dispatcher);
	CMessageDispatcher* GetMessageDispathcer();
};

extern CLocator Locator;