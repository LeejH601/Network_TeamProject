#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual bool HandleMessage(const Telegram& msg);


};

