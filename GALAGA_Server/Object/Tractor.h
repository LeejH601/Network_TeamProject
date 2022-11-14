#pragma once
#include "..\Include\Game.h"
#include "Monster.h"

class CTractor : public CMonster
{
public:
	CTractor();
	virtual ~CTractor();

	virtual bool HandleMessage(const Telegram& telegram);
};

