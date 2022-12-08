#include	"Player.h"
#include	"Bullet.h"
#include	"BulletList.h"
#include	"../Core/Timer.h"
#include	"../Network/NetworkDevice.h"
#include	"../Scene/Scene.h"

CPlayer::CPlayer(int id)
{
	RegisterObject(id);

	m_myBulletList = new CBulletList();
}

CPlayer::~CPlayer()
{
	CObject::~CObject();
	if (m_myBulletList)
		m_myBulletList->EraseAll();

}

bool CPlayer::Init(int type)
{
	POSITION PlayerVector = { 0 , -100 };
	_SIZE PlayerSize = { 60,60 };
	POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
	m_fHP_prototype = 1000.0f;
	m_fSpeed = 300.0f;

	SetType(type); // OT_TERRAN

	switch (m_MyType)
	{
	case TRIBE_TYPE::OT_NONE:
		break;
	case TRIBE_TYPE::OT_TERRAN:
	{
		_SIZE PlayerimgSize = { 46,41 };
		POSITION PlayerimgLT = { 15 * 46, 0 };

		CObject::Init(L"../Image/Terran_img/Wraith.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
	}
		return true;
	case TRIBE_TYPE::OT_ZERG:
	{
		_SIZE PlayerimgSize = { 52,61 };
		POSITION PlayerimgLT = { 10, 101 };

		CObject::Init(L"../Image/Zerg_img/Devourer.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
	}
		return true;
	case TRIBE_TYPE::OT_PROTOSS:
	{
		_SIZE PlayerimgSize = { 31,35 };
		POSITION PlayerimgLT = { 285, 11 };

		CObject::Init(L"../Image/Protoss_img/scout.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
	}
		return true;
	default:
		return false;
	}

}

void CPlayer::Update(float fDeltaTime)
{

}


void CPlayer::Input(float fDeltaTime, CScene* CurScene)
{
	if (GetAsyncKeyState('A') & 0x8000)
	{
		CObject::m_tLTPos.x -= fDeltaTime * m_fSpeed;


		if (CObject::m_tLTPos.x < 0)
			CObject::m_tLTPos.x = 0.0f;


	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		CObject::m_tLTPos.x += fDeltaTime * m_fSpeed;


		if (CObject::m_tLTPos.x > 600 - CObject::m_tSize.x)
			CObject::m_tLTPos.x = 600 - CObject::m_tSize.x;

	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		//CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;

		if (CObject::m_tLTPos.y >= 750 / 2 + 250)
			CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;


		CurScene->imgLT_Move(fDeltaTime);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		CObject::m_tLTPos.y += fDeltaTime * m_fSpeed;


		if (CObject::m_tLTPos.y > 750 - CObject::m_tSize.y)
			CObject::m_tLTPos.y = 750 - CObject::m_tSize.y;

	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		float currentTime = clock();
		if (m_LastFireTime == NULL || currentTime - m_LastFireTime >= 100) {
			POSITION BulletSize = { 18,30 };
			POSITION BulletLTPos = { m_tLTPos.x + m_tSize.x / 2 - BulletSize.x / 2, m_tLTPos.y - BulletSize.y };

			EnterCriticalSection(&Bullet_CS);

			m_BulletList.push_back(CBulletInfo{ BulletLTPos });
			LeaveCriticalSection(&Bullet_CS);
			
			m_LastFireTime = currentTime;
			m_BulletShotCount = 100;

			//CSoundManager::GetInst()->playSound_Effect();
		}
	}

}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position (4byte + 12byte)
	{
		POSITION* pos = new POSITION;
		memcpy(pos, msg.Extrainfo, sizeof(POSITION));

		SetPos(*pos);
		delete pos;
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

void CPlayer::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);
	if (m_myBulletList)
		m_myBulletList->RenderAll(mainhDC, hdc, fDeltaTime);
}