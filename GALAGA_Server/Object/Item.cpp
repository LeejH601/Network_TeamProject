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

bool CItem::Init(ITEM_TYPE itemType, POSITION LTpos)
{
	m_bEnable = true;

	if (itemType == ITEM_TYPE::IT_RANDOM)
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
			m_myType = ITEM_TYPE::IT_STEAMPACK;
		}
		break;
		case 2:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_HPUP;
		}
		break;
		case 3:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_INVINVIBILITY;
		}
		break;
		case 4:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
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
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_STEAMPACK;
		}
		break;
		case ITEM_TYPE::IT_HPUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_HPUP;
		}
		break;
		case ITEM_TYPE::IT_INVINVIBILITY:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_INVINVIBILITY;
		}
		break;
		case ITEM_TYPE::IT_POWERUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			m_myType = ITEM_TYPE::IT_POWERUP;
		}
		break;
		default:
			break;
		}
	}
	
	SendMsgCreateItem(m_myType, LTpos);
	return true;
}

void CItem::Input(float fDeltaTime)
{
}

void CItem::Update(float fDeltaTime)
{
	std::cout << m_iObjID << "- Update()" << std::endl;
	/*CObject::m_tLTPos.y += fDeltaTime * 50;

	if (CObject::m_tLTPos.y > 750)
		m_bEnable = false;*/
}

void CItem::LateUpdate(float fDeltaTime)
{
}

bool CItem::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{

	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);

}

void CItem::SendMsgCreateItem(ITEM_TYPE nType, POSITION pos)
{
	Telegram tel_CreateItem;
	tel_CreateItem.Receiver = 0;
	tel_CreateItem.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	tel_CreateItem.DispatchTime = CTimer::GetInst()->GetTime();
	tel_CreateItem.Extrainfo;
	char* extraInfo = new char[16];
	
	memcpy(&extraInfo[0], &nType, sizeof(ITEM_TYPE));
	
	memcpy(&extraInfo[4], &pos, sizeof(POSITION));
	tel_CreateItem.Extrainfo = extraInfo;

	CObject::SendMessageToClient(tel_CreateItem);
}