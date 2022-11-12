#include	"Player.h"




CPlayer::CPlayer()
{
}

void CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position 
		msg.Extrainfo;
		break;
	case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
		msg.Extrainfo;
		break;
	case MESSAGE_TYPE::Msg_playerHit://extrainfo: X
		break;
	default:
		break;
	}
}
