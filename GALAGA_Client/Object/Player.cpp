#include	"Player.h"
CPlayer::CPlayer()
{
}

bool CPlayer::Init()
{
	POSITION PlayerVector = { 0 , -100 };
	_SIZE PlayerSize = { 60,60 };
	POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
	m_fHP_prototype = 1000.0f;
	m_fSpeed = 300.0f;

	SetType(1); // 임시적으로 OT_TERRAN으로 설정

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