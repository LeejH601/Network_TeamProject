#pragma once
#include "../Include/Game.h"
#include "Object.h"

class CBulletList
{
public:
	CBulletList();
	CBulletList(int id); // 소유하고 있는 오브젝트의 id
	~CBulletList();

public:
	// Bullet 추가
	void AddBullet(int id, POSITION playerLT, POSITION playerSize, float Speed);
	void AddBullet(int id, POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);

	// Update
	void Update(float fDeltaTime);
	void Update(float fDeltaTime, _SIZE _size);
	void LateUpdate(float fDeltaTime);

	// Bullet Render
	void RenderAll(HDC mainDC, HDC hdc, float fDeltaTime);

	// Bullet Collision
	// 반환값: 충돌 횟수, 인자: 오브젝트 위치, 사이즈
	int Collision(float fDeltatime, POSITION ObjectLT, _SIZE ObjectSize);

	
	// Bullet Erase
	void Erase(class CBullet* delNode);
	bool EraseAll();

	void Set_Object(int id);

private:
	float m_fAttack = 100; // 총알 공격력 


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
	int	ObjectId = -1; // 현재 해당 불렛리스트를 소유하고 있는 오브젝트 id
};

