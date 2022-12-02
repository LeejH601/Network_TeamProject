#pragma once
#include "..\Include\Game.h"
#include "Monster.h"

class CBoss : public CMonster
{
public:
	CBoss();
	virtual ~CBoss();

	virtual  bool Init(POSITION LTpos, const OBJECT_TYPE& type, POSITION Vector, int stageNum);
	virtual void Update(float fDeltaTime);

	virtual bool HandleMessage(const Telegram& telegram);
};

