#pragma once
#include "Object.h"

class CNetworkDevice;
class CPlayer : public CObject
{
private:
	bool			m_bDie = true;
	float			m_fSpeed;	// Player 의 속도 입니다
	TRIBE_TYPE		m_MyType; // Player_Type

private:
	class CBulletList* m_myBulletList;

public:
	class CBulletList* GetmyBulletList()
	{
		if (m_myBulletList)
			return m_myBulletList;
		else
			return NULL;
	}
public:
	CPlayer();
	~CPlayer();
	int Init();
	float GetSpeed()
	{
		return m_fSpeed;
	}
	void SetSpeed(float Speed)
	{
		m_fSpeed = Speed;
	}
	virtual	void Update(float fDeltaTime);
	void SendCreateMessage(CNetworkDevice* pNetworkDevice, OBJECT_TYPE obj_type);
	virtual bool HandleMessage(const Telegram& msg);
};

