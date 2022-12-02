#pragma once
#include "Object.h"

class CBulletInfo
{
public:
	CBulletInfo(POSITION LTPos) { m_LTPos = LTPos; }
	POSITION m_LTPos;
};

class CBullet : public CObject
{
public:
	CBullet();
	virtual bool HandleMessage(const Telegram& msg);

	// Bullet ���� �ʱ�ȭ
	// -Player Bullet
	virtual  bool Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed);
	// -Monster Bullet
	virtual  bool Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);

	virtual	void Update(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);

private:
	bool	m_bEnable; // false�� ��� ����

	float	m_fSpeed;	// �Ѿ� ���ǵ�
	float	m_MaxRange;// �Ѿ� �����Ÿ� 
	float	m_Range;
public:
	bool GetEnbale(){return m_bEnable;}
	void SetEnalbeFalse(){m_bEnable = false;}
};
