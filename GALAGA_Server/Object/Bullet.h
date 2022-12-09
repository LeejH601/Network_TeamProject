#pragma once
#include "..\Include\Game.h"
#include "Object.h"

class CBullet : public CObject
{

public:
	CBullet(); 
	~CBullet();
	virtual bool HandleMessage(const Telegram& msg);

	// Bullet ���� �ʱ�ȭ
	// -Player Bullet
	virtual  bool Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed);
	// -Monster Bullet
	virtual  bool Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);
	virtual	void Update(float fDeltaTime);

	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);

protected:
	bool	m_bEnable; // false�� ��� ����

	float	m_fSpeed;	// �Ѿ� ���ǵ�
	float	m_MaxRange;// �Ѿ� �����Ÿ� 
	float	m_Range;



public:
	bool GetEnbale() { return GetObjectState() != OBJECT_STATE::ERASE; }
	void SetEnalbeFalse() { SetState(OBJECT_STATE::DESTORY); }


};