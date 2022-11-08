#pragma once
#include "../Game.h"

// 양방향 연결리스트로 관리합니다...
typedef struct _TagNodeItem
{
	class CItem* item = nullptr;
	_TagNodeItem* pNext = nullptr;
	_TagNodeItem* pPrev = nullptr;
}INODE, * PINODE;



class CItemList
{
private:
	friend class CItem;

public:
	CItemList();
	~CItemList();

private:
	PINODE m_pBegin;
	PINODE m_pEnd;
	int m_Count;


private:
	float m_fAttack = 100; // 총알 공격력 


public:
	// 공격력을 반환합니다. 
	float GetAttack()
	{
		return m_fAttack;

	}
	// 공격력을 설정합니다...
	void SetAttack(float Attack)
	{
		m_fAttack = Attack;
	}
	void AddAttack()
	{
		m_fAttack += 50.0f;

	}
public:
	void Init();


public:
	// 충돌체크할 오브젝트의 위치와 사이즈를 받습니다.. 몇번 충돌 했는지를 반환합니다...
	bool Collision(float fDeltatime, POSITION ObjectLT, POSITION ObjectSize, class CPlayer* Player);

public:
	void PushBack(ITEM_TYPE itemType);

	void PushBack(ITEM_TYPE itemType,POSITION playerLT, POSITION playerSize, float Speed);
	void PushBack(ITEM_TYPE itemType, POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);	// 리스트에 Bullet 을 추가합니다...
	void Erase(PINODE delNode = nullptr);														// 리스트내 해당 bullet 을 삭제합니다...

	void RenderAll(HDC mainhDC, HDC hdc, float fDeltaTime);										// 현재 총알 리스트를 전부 출력합니다..
	bool EraseAll();																			// 현재 총알 리스트를 전부 삭제합니다..

	void Update(float fDeltaTime);
	bool Empty()
	{
		if (m_Count == 0)
			return true;
		else
			return false;

	}

};

