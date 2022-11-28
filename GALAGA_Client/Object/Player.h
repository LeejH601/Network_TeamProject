#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	TRIBE_TYPE		m_MyType; // Player_Type
	float			m_fSpeed; // Player �ӵ�
	float			m_fHP_prototype; // Player Hp
	POSITION		m_tLastLTPos;				
public:
	CPlayer(int id);

	float GetSpeed()
	{
		return m_fSpeed;
	}

	void SetSpeed(float Speed)
	{
		m_fSpeed = Speed;
	}

	void SetType(int num)
	{
		if (num >= 0 && num <= 3)
			m_MyType = (TRIBE_TYPE)num;
	}

	TRIBE_TYPE GetMyType()
	{
		return m_MyType;
	}

	virtual bool Init() { return true; }
	virtual bool Init(int type);
	virtual void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual bool HandleMessage(const Telegram& msg);
	virtual void Render(HDC mainhDC, HDC hdc, float fDeltaTime);
};
