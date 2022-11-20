#include	"Bullet.h"




CBullet::CBullet()
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
		break;
	}

	return false;
}


bool CBullet::Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed)
{
	// 이미지 파일 크기 값 변수로 바꾸기
	CObject::Init(L"../Bin/Item_img/Bullets.png", PlayerLT, POSITION(0, 1),
		PlayerSize, 1000.0f, POSITION(8, 15), POSITION(84, 42), PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	CObject::Init(L"../Bin/Item_img/Bullets.png", MonsterLT, BulletVector,
		MonsterSize, 1000.0f, POSITION(16, 16), POSITION(167, 297), PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 1000.0f;
	m_Range = 0.0f;

	return false;
}

bool CBullet::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);
}