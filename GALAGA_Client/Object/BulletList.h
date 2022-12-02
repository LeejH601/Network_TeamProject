#pragma once
#include "../Include/Game.h"
#include "Object.h"

class CBulletList
{
public:
	CBulletList();
	CBulletList(int id); // �����ϰ� �ִ� ������Ʈ�� id
	~CBulletList();

public:
	// Bullet �߰�
	void AddBullet(int id, POSITION playerLT, POSITION playerSize, float Speed);
	void AddBullet(int id, POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);

	// Update
	void Update(float fDeltaTime);
	void Update(float fDeltaTime, _SIZE _size);
	void LateUpdate(float fDeltaTime);

	// Bullet Render
	void RenderAll(HDC mainDC, HDC hdc, float fDeltaTime);

	// Bullet Collision
	// ��ȯ��: �浹 Ƚ��, ����: ������Ʈ ��ġ, ������
	int Collision(float fDeltatime, POSITION ObjectLT, _SIZE ObjectSize);

	
	// Bullet Erase
	void Erase(class CBullet* delNode);
	bool EraseAll();

	void Set_Object(int id);

private:
	float m_fAttack = 100; // �Ѿ� ���ݷ� 


public:
	// ���ݷ� ��ȯ
	float GetAttack()
	{
		return m_fAttack;

	}
	// ���ݷ� ����
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
	int	ObjectId = -1; // ���� �ش� �ҷ�����Ʈ�� �����ϰ� �ִ� ������Ʈ id
};

