#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	bool m_bDie = true;
	float m_fSpeed;	// Player 의 속도 입니다
public:
	CPlayer();

	int Init();
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

