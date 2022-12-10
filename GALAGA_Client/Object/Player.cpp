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

	if (m_Invincibility_img == NULL)
		m_Invincibility_img.Load(TEXT("./Image/Item_img/invincibility (2).png"));

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
	switch (m_eObjState)
	{
	case OBJECT_STATE::DONDESTORY:
		AnimationTimer -= fDeltaTime;
		if (AnimationTimer < FLT_EPSILON)
		{
			AnimationTimer = 0.1f;
			AnimationX += 1;
			if (AnimationX >= 5)
			{
				AnimationX = 0;
				AnimationY = (AnimationY + 1) % 3;
			}
		}
		break;
	case OBJECT_STATE::RESPAWN:
		AnimationTimer -= fDeltaTime;
		if (AnimationTimer < FLT_EPSILON)
		{
			AnimationTimer = 0.1f;
			AnimationX += 1;
			if (AnimationX >= 5)
			{
				AnimationX = 0;
				AnimationY = (AnimationY + 1) % 3;
			}
		}
		break;
	default:
		break;
	}
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
		CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;

		if (CObject::m_tLTPos.y >= 750 / 2 + 250)
			CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		CObject::m_tLTPos.y += fDeltaTime * m_fSpeed;


		if (CObject::m_tLTPos.y > 750 - CObject::m_tSize.y)
			CObject::m_tLTPos.y = 750 - CObject::m_tSize.y;

	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		float currentTime = clock();
		if (m_LastFireTime == NULL || currentTime - m_LastFireTime >= 100) {
			POSITION BulletSize = { 18,30 };
			POSITION BulletLTPos = { m_tLTPos.x + m_tSize.x / 2 - BulletSize.x / 2, m_tLTPos.y - BulletSize.y };

			EnterCriticalSection(&Game_CS);

			m_BulletList.push_back(CBulletInfo{ BulletLTPos });
			LeaveCriticalSection(&Game_CS);
			
			m_LastFireTime = currentTime;
			m_BulletShotCount = 100;

			//CSoundManager::GetInst()->playSound_Effect();
		}
	}

}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch (static_cast<MESSAGE_TYPE>(msg.Msg))
	{
	case MESSAGE_TYPE::Msg_objectMove:
	{
		POSITION* pos = new POSITION;
		memcpy(pos, msg.Extrainfo, sizeof(POSITION));

		SetPos(*pos);
		delete pos;
	}
	return true;
	case MESSAGE_TYPE::Msg_objectChangeState:
	{	
		OBJECT_STATE* state = new OBJECT_STATE;
		memcpy(state, msg.Extrainfo, sizeof(OBJECT_STATE));

		if (m_eObjState == *state)
		{
			delete state;
			return true;
		}
		AnimationX = 0;
		AnimationY = 0;
		AnimationTimer = 0.1f;
		m_eObjState = *state;
		if (m_eObjState == OBJECT_STATE::RESPAWN)
			SetPos(POSITION{ 300, 600 });
		delete state;
	}
	return true;
	default:
		break;
	}
	return false;
}

void CPlayer::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	if (m_eObjState == OBJECT_STATE::DONDESTORY || m_eObjState == OBJECT_STATE::RESPAWN)
	{
		m_Invincibility_img.Draw(hdc, CObject::m_tLTPos.x - (m_tSize.x / 3) - 10,
			CObject::m_tLTPos.y - (m_tSize.y / 3) - 10, CObject::m_tSize.x + (m_tSize.x / 2) + 20,
			CObject::m_tSize.y + (m_tSize.y / 2) + 10, AnimationX * 190, AnimationY * 190, 190, 190);
	}

	if (m_eObjState != OBJECT_STATE::DESTORY)
		CObject::Render(mainhDC, hdc, fDeltaTime);

	if (m_myBulletList)
		m_myBulletList->RenderAll(mainhDC, hdc, fDeltaTime);
}