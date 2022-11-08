#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& item)
{
}

CItem::~CItem()
{
}

bool CItem::Init(ITEM_TYPE itemType, POSITION LTpos)
{
	m_bEnable = true;

	if (itemType == ITEM_TYPE::IT_RANDOM)
	{
		int SetItem = 1 + rand() % 4;

		POSITION Size = { 40,40 };
		POSITION LT = LTpos;
		POSITION vector = { 0,1 };
		POSITION imgLT = { 1,1 };
		POSITION imgSIze = { 59,59 };

	
		switch (SetItem)
		{
		case 1:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_ATKSPDUP.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_STEAMPACK;
		}
		break;
		case 2:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_HPUP.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_HPUP;
		}
		break;
		case 3:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_INVINCIBILITY.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_INVINVIBILITY;
		}
		break;
		case 4:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_PowUp.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_POWERUP;
		}
		break;
		default:
			break;
		}

	}
	else
	{
		POSITION Size = { 40,40 };
		POSITION vector = { 0,1 };
		POSITION imgLT = { 1,1 };
		POSITION imgSIze = { 59,59 };

		switch (itemType)
		{
		case ITEM_TYPE::IT_STEAMPACK:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_ATKSPDUP.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_STEAMPACK;
		}
		break;
		case ITEM_TYPE::IT_HPUP:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_HPUP.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_HPUP;
		}
		break;
		case ITEM_TYPE::IT_INVINVIBILITY:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_INVINCIBILITY.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_INVINVIBILITY;
		}
		break;
		case ITEM_TYPE::IT_POWERUP:
		{
			CObject::Init(TEXT("../Bin/Item_img/icon_PowUp.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_POWERUP;
		}
		break;
		default:
			break;
		}
	}
	

	return true;
}

void CItem::Input(float fDeltaTime)
{
}

void CItem::Update(float fDeltaTime)
{
	CObject::m_tLTPos.y += fDeltaTime * 50;


	if (CObject::m_tLTPos.y > 750)
		m_bEnable = false;


}

void CItem::LateUpdate(float fDeltaTime)
{
}

bool CItem::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{

	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);

}

void CItem::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);

}
