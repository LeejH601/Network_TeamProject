#include "Player.h"
#include "../Core.h"
#include "../Locator.h"
#include "../Core/Timer.h"
#include "../Network/NetworkDevice.h"
#include "../Object/BulletList.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	CObject::~CObject();

	if (m_myBulletList)
		m_myBulletList->EraseAll();

}

int CPlayer::Init()
{
	m_myBulletList = new CBulletList;

	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	_SIZE PlayerSize = { 60,60 };
	POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };

	m_tLTPos = PlayerLT;

	m_bDie = false;
	m_fSpeed = 300.0f;

	return m_iObjID;
}
void CPlayer::Update(float fDeltaTime)
{
	if (m_myBulletList)
		m_myBulletList->Update(fDeltaTime);
}
bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectCreate:// extrainfo: ObjectType, Position
	{
		int ObjectType;
		POSITION Position;
		POSITION BulletSize = { 18,30 };
		memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
		memcpy(&Position, (char*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
		if (ObjectType == (int)OBJECT_TYPE::PLAYER_BULLET) // Bullet »ý¼º
		{
			m_myBulletList->AddBullet(Position, BulletSize, 800.0f);
		}
		return true;
	}
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position (4byte + 12byte)
	{
		POSITION* pos = new POSITION;
		memcpy(pos, msg.Extrainfo, sizeof(POSITION));
		
		SetPos(*pos);
		delete pos;
		return true;
	}
	case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
	{
		int ObjectState;
		memcpy(&ObjectState, msg.Extrainfo, sizeof(int));
		return true;
	}
	default:
		break;
	}

	return false;

}
