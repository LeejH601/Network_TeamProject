#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	float m_fSpeed;	// Player �� �ӵ� �Դϴ�
public:
	CPlayer();

	float GetSpeed()
	{
		return m_fSpeed;
	}

	void SetSpeed(float Speed)
	{
		m_fSpeed = Speed;
	}

	virtual bool HandleMessage(const Telegram& msg);
};

