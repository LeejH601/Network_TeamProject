#pragma once
#include "../Include/Game.h"
#include "Object.h"

class CBulletList
{
public:
	CBulletList();
	~CBulletList();

public:
	// Bullet 추가
	void AddBullet(POSITION playerLT, POSITION playerSize, float Speed);
	void AddBullet(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);

	// Update
	void Update(float fDeltaTime);
	void Update(float fDeltaTime, _SIZE _size);
	void LateUpdate(float fDeltaTime);

	// Bullet Collision
	// 반환값: 충돌 횟수, 인자: 오브젝트 위치, 사이즈
	int Collision(float fDeltatime, POSITION ObjectLT, _SIZE ObjectSize);

	
	// Bullet Erase
	void Erase(class CBullet* delNode);
	bool EraseAll();


private:
	float m_fAttack = 100.f; // 총알 공격력 


public:
	// 공격력 반환
	float GetAttack()
	{
		return m_fAttack;

	}
	// 공격력 설정
	void SetAttack(float Attack)
	{
		m_fAttack = Attack;
	}
	void AddAttack()
	{
		m_fAttack += 50.0f;
	}
	
	bool Empty()
	{
		if (m_listBulletList.empty())
			return true;
		else
			return false;

	}
private:
	std::list<class CBullet*> m_listBulletList;
public:
	std::list<class CBullet*>* GetBulletList() { return &m_listBulletList; }
};

