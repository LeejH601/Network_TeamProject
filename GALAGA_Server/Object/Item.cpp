#include "Player.h"
#include "BulletList.h"
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

void CItem::SetDestroy()
{
	SetState(OBJECT_STATE::DESTORY);
	m_fStateTerm = 0.0f;
	m_bEnable = false;
}

void CItem::SetEffect(CPlayer* pPlayer)
{
	switch (m_eObjType)
	{
	case OBJECT_TYPE::IT_STEAMPACK:
		pPlayer->AddBullet();
		break;
	case OBJECT_TYPE::IT_HPUP:
		pPlayer->SetDondestroy();
		break;
	case OBJECT_TYPE::IT_INVINVIBILITY:
		pPlayer->SetDondestroy();
		break;
	case OBJECT_TYPE::IT_POWERUP:
		pPlayer->GetmyBulletList()->AddAttack();
		break;
	default:
		break;
	}
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
			CObject::SetObjType(OBJECT_TYPE::IT_STEAMPACK);
		}
		break;
		case 2:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_HPUP);
		}
		break;
		case 3:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_INVINVIBILITY);
		}
		break;
		case 4:
		{
			CObject::Init(LT, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_POWERUP);
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
			CObject::SetObjType(OBJECT_TYPE::IT_STEAMPACK);
		}
		break;
		case OBJECT_TYPE::IT_HPUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_HPUP);
		}
		break;
		case OBJECT_TYPE::IT_INVINVIBILITY:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_INVINVIBILITY);
		}
		break;
		case OBJECT_TYPE::IT_POWERUP:
		{
			CObject::Init(LTpos, vector, Size, 100.0f, PLAYER_TYPE::PT_MONSTER);
			CObject::SetObjType(OBJECT_TYPE::IT_POWERUP);
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
		CObject::m_tLTPos.y += fDeltaTime * 250.0f;

		if (CObject::m_tLTPos.y > 850.0f)
		{
			SetDestroy();
		}
	}
	else
	{
		switch (m_eObjState) {
		case OBJECT_STATE::DESTORY:
			m_fStateTerm += fDeltaTime;
			// 3초 뒤 State가 Erase로 바뀜
			if (m_fStateTerm >= 3.0f)
				SetState(OBJECT_STATE::ERASE);
			break;
		case OBJECT_STATE::ERASE:
			break;
		}
	}
}

void CItem::LateUpdate(float fDeltaTime)
{
}

bool CItem::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{

	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);

}