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

bool CItem::Init(OBJECT_TYPE itemType, POSITION LTpos)
{
	m_bEnable = true;

	if (itemType == OBJECT_TYPE::IT_RANDOM)
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
			CObject::Init(TEXT("../Image/Item_img/icon_ATKSPDUP.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_STEAMPACK;
		}
		break;
		case 2:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_HPUP.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_HPUP;
		}
		break;
		case 3:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_INVINCIBILITY.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_INVINVIBILITY;
		}
		break;
		case 4:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_PowUp.png"), LT, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
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
			CObject::Init(TEXT("../Image/Item_img/icon_ATKSPDUP.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_STEAMPACK;
		}
		break;
		case OBJECT_TYPE::IT_HPUP:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_HPUP.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_HPUP;
		}
		break;
		case OBJECT_TYPE::IT_INVINVIBILITY:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_INVINCIBILITY.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
			m_myType = OBJECT_TYPE::IT_INVINVIBILITY;
		}
		break;
		case OBJECT_TYPE::IT_POWERUP:
		{
			CObject::Init(TEXT("../Image/Item_img/icon_PowUp.png"), LTpos, vector, Size, 100.0f, imgSIze, imgLT, PLAYER_TYPE::PT_MONSTER);
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
}

void CItem::LateUpdate(float fDeltaTime)
{
}

void CItem::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);

}

bool CItem::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_objectChangeState:
		switch(static_cast<OBJECT_STATE>((int&)(telegram.Extrainfo)))
		{
		case OBJECT_STATE::ERASE:
			CObjectManager::GetInst()->RemoveObject(this);
			m_bEnable = false;
			return true;
		default:
			break;
		}
		break;
	case MESSAGE_TYPE::Msg_objectMove:
		CObject::HandleMessage(telegram);
		return true;
	default:
		break;
	}

	return false;
}
