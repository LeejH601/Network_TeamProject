#pragma once
#include "Object.h"

class CBullet : public CObject
{
public:
	CBullet();
	virtual bool HandleMessage(const Telegram& msg);


};

