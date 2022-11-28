#include	"Player.h"
CPlayer::CPlayer()
{
}

bool CPlayer::Init()
{
	int i = 0;

	POSITION PlayerVector = { 0 , -100 };
	_SIZE PlayerSize = { 60,60 };
	POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
	POSITION PlayerimgSize = { 46,41 };
	POSITION PlayerimgLT = { 15 * 46, 0 };

	CObject::Init(L"../Image/Terran_img/Wraith.png", PlayerLT, PlayerVector, PlayerSize, 1000.0f, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
	m_fSpeed = 300.0f;

	return true;
}

void CPlayer::Input(float fDeltaTime)
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
}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position (4byte + 12byte)
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

void CPlayer::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);
}