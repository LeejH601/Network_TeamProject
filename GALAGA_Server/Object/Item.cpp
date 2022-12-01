#include "Item.h"
#include "../Core/Timer.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& item)
{
}

CItem::~CItem()
{
}

bool CItem::Init(OBJECT_TYPE itemType, POSITION LTpos)
{
	m_bEnable = true;

	if (itemType == OBJECT_TYPE::IT_RANDOM)
	{
		int SetItem = 1 + rand() % 4;

		POSITION Size = { 40,40 };
		POSITION LT = LTpos;
		POSITION vector = { 0,1 };

	
		switch (SetItem)
		{
		case 1:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_STEAMPACK;
		}
		break;
		case 2:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_HPUP;
		}
		break;
		case 3:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_INVINVIBILITY;
		}
		break;
		case 4:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_POWERUP;
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
		case OBJECT_TYPE::IT_STEAMPACK:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_STEAMPACK;
		}
		break;
		case OBJECT_TYPE::IT_HPUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_HPUP;
		}
		break;
		case OBJECT_TYPE::IT_INVINVIBILITY:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_INVINVIBILITY;
		}
		break;
		case OBJECT_TYPE::IT_POWERUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_POWERUP;
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
	if (m_bEnable)
	{
		CObject::m_tLTPos.y += fDeltaTime * 2.5f;

		if (CObject::m_tLTPos.y > 750.0f)
			m_bEnable = false;
	}
}

void CItem::LateUpdate(float fDeltaTime)
{
}

bool CItem::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{

	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);

}