#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	TRIBE_TYPE		m_MyType; // Player_Type
	float			m_fSpeed; // Player �ӵ�
	float			m_fHP_prototype; // Player Hp
	POSITION		m_tLastLTPos;
	//Bullet
private:
	float		m_LastFireTime = 0.f;
	int			m_BulletShotCount;
	int			m_BulletNum = 5;		 // 총알 개수(아이템을 통해 총알 개수 증가)
private:
	std::list<class CBulletInfo> m_BulletList;
	class CBulletList* m_myBulletList;

public:
	class CBulletList* GetmyBulletList()
	{
		if (m_myBulletList)
			return m_myBulletList;
		return NULL;
	}
	class std::list<class CBulletInfo>* GetmyBulletInfoList()
	{
		return &m_BulletList;
	}
public:
	CPlayer(int id);
	~CPlayer();
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
	void AddBullet() // Item 충돌시 불렛 개수 증가
	{
		if (++m_BulletNum >= 5)
			m_BulletNum = 5;
	}
	void SendMsgAddBullet();


	virtual bool Init() { return true; }
	virtual bool Init(int type);
	virtual void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual bool HandleMessage(const Telegram& msg);
	virtual void Render(HDC mainhDC, HDC hdc, float fDeltaTime);



};
