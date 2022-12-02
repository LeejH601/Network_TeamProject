#include "Bullet.h"
#include "../Network/NetworkDevice.h"
#include "../Core.h"
#include "../Locator.h"


CBullet::CBullet()
{

}

CBullet::~CBullet()
{

}


bool CBullet::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position 
	{
		int ObjectType;
		POSITION Position;
		memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
		memcpy(&Position, (char*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
		return true;
	}
	case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
	{
		int ObjectState;
		memcpy(&ObjectState, msg.Extrainfo, sizeof(int));
		return true;
	}
	default:
		return true;
	}

	return false;
}


bool CBullet::Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed)
{
	// 이미지 파일 크기 값 변수로 바꾸기
	CObject::Init(PlayerLT, POSITION(0, -1), PlayerSize, 1000.0f, PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;
	
	CObject::SetObjType(OBJECT_TYPE::PLAYER_BULLET);

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	CObject::Init(MonsterLT, BulletVector, MonsterSize, 1000.0f, PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 1000.0f;
	m_Range = 0.0f;

	return true;
}

void CBullet::Update(float fDeltaTime)
{

	CObject::SetPos(CObject::GetPos() + ((CObject::GetVector() * fDeltaTime) * m_fSpeed));

	m_Range += fDeltaTime * m_fSpeed;

	if (m_Range >= m_MaxRange)
		SetEnalbeFalse();
}

bool CBullet::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);
}

