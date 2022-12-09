#pragma once
#include "Object.h"

class CNetworkDevice;
class CPlayer : public CObject
{
private:
	bool			m_bDie = true;
	float			m_fSpeed;	// Player �� �ӵ� �Դϴ�
	int				m_BulletNum = 1;		 // 총알 개수(아이템을 통해 총알 개수 증가)
	float			m_fDondestroyTime = 0.5f;
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
	void AddBullet() // Item 충돌시 불렛 개수 증가
	{
		if (++m_BulletNum >= 5)
			m_BulletNum = 5;
	}
	void SetDondestroy();
	void SetRespawn();
	virtual	void Update(float fDeltaTime);
	virtual bool HandleMessage(const Telegram& msg);
};

