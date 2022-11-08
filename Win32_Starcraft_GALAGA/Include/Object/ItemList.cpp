#include "ItemList.h"
#include "Item.h"
#include "Object.h"
#include "Player.h"



CItemList::CItemList()
{

}

CItemList::~CItemList()
{
	EraseAll();
	delete m_pBegin;
	delete m_pEnd;

}


void CItemList::Init()
{

	m_pBegin = new INODE;
	m_pEnd = new INODE;

	m_pBegin->pNext = m_pEnd;
	m_pEnd->pNext = NULL;

	m_pBegin->pPrev = NULL;
	m_pEnd->pPrev = m_pBegin;


	m_Count = 0;
}

bool CItemList::Collision(float fDeltatime, POSITION ObjectLT, POSITION ObjectSize, CPlayer* Player)
{


	// 충돌횟수
	int CollisionCheckNum = 0;
	for (PINODE pINODE = m_pBegin->pNext; pINODE != m_pEnd; pINODE = pINODE->pNext)
	{
		if (pINODE)
		{
			// 총알과 해당 객체가 충돌했다면 충돌 갯수를 늘려준다...
			if (pINODE->item->Collision(fDeltatime, ObjectLT, ObjectSize))
			{

				CollisionCheckNum += 1;
				
				switch (pINODE->item->GetType())
				{
				case ITEM_TYPE::IT_STEAMPACK:
				{
					Player->AddBullet();

				}
				break;
				case ITEM_TYPE::IT_HPUP:
				{
					Player->SetHPPrototype();

				}
				break;
				case ITEM_TYPE::IT_INVINVIBILITY:
				{
					Player->SetINVINVIBILITY(true);

				}
				break;
				case ITEM_TYPE::IT_POWERUP:
				{
				Player->AddAttack();
				}
				break;
				default:
					break;
				}

				PINODE delINODE = pINODE;
				pINODE = pINODE->pPrev;
				Erase(delINODE);

			}
		}
	}


	return true;

}


void CItemList::PushBack(ITEM_TYPE itemType)
{
	PINODE NewINODE = new INODE;
	NewINODE->item = new CItem;
	NewINODE->item->Init(itemType, {1.f + rand()% 600, -30});

	NewINODE->pNext = m_pEnd;
	m_pEnd->pPrev->pNext = NewINODE;

	NewINODE->pPrev = m_pEnd->pPrev;
	m_pEnd->pPrev = NewINODE;

	m_Count += 1;
}

void CItemList::PushBack(ITEM_TYPE itemType,POSITION playerLT, POSITION playerSize, float Speed)
{
	if (this == nullptr)
		int i = 0;


	PINODE NewINODE = new INODE;
	POSITION itemSize = { 18,30 };
	POSITION itemLTPos = { playerLT.x + playerSize.x / 2 - itemSize.x / 2, playerLT.y - itemSize.y };

	NewINODE->item = new CItem;
	NewINODE->item->Init(itemType, playerLT);

	NewINODE->pNext = m_pEnd;
	m_pEnd->pPrev->pNext = NewINODE;

	NewINODE->pPrev = m_pEnd->pPrev;
	m_pEnd->pPrev = NewINODE;

	m_Count += 1;

}

void CItemList::PushBack(ITEM_TYPE itemType, POSITION MonsterLT, _SIZE MonsterSize, POSITION itemVector, float Speed)
{
	if (this == nullptr)
		int i = 0;


	PINODE NewINODE = new INODE;
	POSITION itemSize = { MonsterSize.x,MonsterSize.y };
	POSITION itemLTPos = { MonsterLT.x + MonsterSize.x / 2 - itemSize.x / 2, MonsterLT.y - itemSize.y };

	NewINODE->item = new CItem;
	NewINODE->item->Init(itemType, MonsterLT);

	NewINODE->pNext = m_pEnd;
	m_pEnd->pPrev->pNext = NewINODE;

	NewINODE->pPrev = m_pEnd->pPrev;
	m_pEnd->pPrev = NewINODE;

	m_Count += 1;
}

void CItemList::Erase(PINODE delINODE)
{
	if (delINODE == nullptr || delINODE == m_pEnd || delINODE == m_pBegin)
		return;
	PINODE DeleteINODE = delINODE;

	delINODE->pPrev->pNext = delINODE->pNext;
	delINODE->pNext->pPrev = delINODE->pPrev;

	DeleteINODE->item->~CItem();
	delete DeleteINODE;


	m_Count -= 1;

}

void CItemList::RenderAll(HDC mainhDC, HDC hdc, float fDeltaTime)
{

	for (PINODE pINODE = m_pBegin->pNext; pINODE != m_pEnd; pINODE = pINODE->pNext)
	{
		if (pINODE)
			pINODE->item->Render(mainhDC, hdc, fDeltaTime);
	}

}

bool CItemList::EraseAll()
{
	if (Empty())
		return true;

	for (PINODE pINODE = m_pBegin->pNext; pINODE != m_pEnd; pINODE = m_pBegin->pNext)
	{
		PINODE DelINODE = pINODE;
		m_pBegin->pNext = DelINODE->pNext;

		if (DelINODE)
		{
			delete DelINODE;
			m_Count -= 1;
		}

	}

	if (Empty())
		return true;
	else
		return false;


}

void CItemList::Update(float fDeltaTime)
{
	// itemList 내에서 모든 item 의 거리를 이동시킨다...
	for (PINODE pINODE = m_pBegin->pNext; pINODE != m_pEnd; pINODE = pINODE->pNext)
	{
		if (pINODE->item)
			pINODE->item->Update(fDeltaTime);

		if (pINODE->item->GetEnbale() == false)
		{
			PINODE delINODE = pINODE;
			pINODE = pINODE->pPrev;
			Erase(delINODE);

		}
	}

}

