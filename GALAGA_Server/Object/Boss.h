#pragma once
#include "..\Include\Game.h"
#include "Monster.h"

class CBoss : public CMonster
{
public:
	CBoss();
	virtual ~CBoss();

	virtual bool HandleMessage(const Telegram& telegram);
};

