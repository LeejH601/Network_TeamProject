#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	CObject::~CObject();
}

bool CBullet::Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed)
{
	// 플레이어 위치 기준으로 총알의 위치를 초기화 합니다... 
	POSITION PlayerVector = { 0 ,  -1 };

	// 화면이 아니라 이미지 (png 파일에서의 이미지 입니다... 고정 값 )
	POSITION BulletimgSize = { 8,15 };
	POSITION BulletimgLT = { 84,42 }; //  이미지 파일에서의 x y  좌표입니다...

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;



	CObject::Init(L"../Bin/Terran_img/Wraith.png", PlayerLT, PlayerVector,
		PlayerSize, 1000.0f, BulletimgSize, BulletimgLT, PLAYER_TYPE::PT_MONSTER);

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	POSITION BulletimgSize = { 16,16 };
	POSITION BulletimgLT = { 167,297 }; //  이미지 파일에서의 x y  좌표입니다...

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 1000.0f;
	m_Range = 0.0f;



	CObject::Init(L"../Bin/Item_img/Bullets.png", MonsterLT, BulletVector,
		MonsterSize, 1000.0f, BulletimgSize, BulletimgLT, PLAYER_TYPE::PT_MONSTER);

	return false;
}

void CBullet::Input(float fDeltaTime, CScene* CurScene)
{
}

void CBullet::Update(float fDeltaTime)
{

	CObject::SetPos(CObject::GetPos() + ((CObject::GetVector() * fDeltaTime) * m_fSpeed));

	m_Range += fDeltaTime * m_fSpeed;

	if (m_Range >= m_MaxRange)
		SetEnalbeFalse();

}

void CBullet::LateUpdate(float fDeltaTime)
{
}


bool CBullet::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);

}

void CBullet::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);

}


