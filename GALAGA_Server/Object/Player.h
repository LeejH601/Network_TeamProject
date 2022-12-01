#pragma once
#include "Object.h"

class CNetworkDevice;
class CPlayer : public CObject
{
private:
	bool			m_bDie = true;
	float			m_fSpeed;	// Player �� �ӵ� �Դϴ�

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
	virtual bool HandleMessage(const Telegram& msg);
};

