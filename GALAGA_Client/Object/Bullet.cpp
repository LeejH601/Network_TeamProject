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
		CObject::HandleMessage(msg);
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
	// 화면이 아니라 이미지 (png 파일에서의 이미지 입니다... 고정 값 )
	POSITION BulletimgSize = { 8,15 };
	POSITION BulletimgLT = { 84,42 }; //  이미지 파일에서의 x y  좌표입니다...
	// 이미지 파일 크기 값 변수로 바꾸기
	CObject::Init(L"../Image/Terran_img/Wraith.png", PlayerLT, POSITION(0, -1),
		PlayerSize, 1000.0f, BulletimgSize, BulletimgLT, PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	POSITION BulletimgSize = { 16,16 };
	POSITION BulletimgLT = { 167,297 };
	CObject::Init(L"../Image/Item_img/Bullets.png", MonsterLT, BulletVector, MonsterSize, 1000.0f, BulletimgSize, BulletimgLT, PLAYER_TYPE::PT_MONSTER);

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

void CBullet::Update(float fDeltaTime)
{

}