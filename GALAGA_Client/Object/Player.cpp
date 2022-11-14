#include	"Player.h"




CPlayer::CPlayer()
{
}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position (4byte + 12byte)
		int ObjectType;
		POSITION Position;
		memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
		memcpy(&Position, (int*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
		return true;
	case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
		int ObjectState;
		memcpy(&ObjectState, msg.Extrainfo, sizeof(int));
		return true;
	default:
		break;
	}

	return false;

}
