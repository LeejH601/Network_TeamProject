#include "Monster.h"


CMonster::CMonster()
{

}

CMonster::~CMonster()
{

}


bool CMonster::HandleMessage(const Telegram& telegram)
{
	MESSAGE_TYPE msg_type = (MESSAGE_TYPE)telegram.Msg;

	switch (msg_type)
	{
	case MESSAGE_TYPE::Msg_objectMove:
	{
		POSITION* pos = (POSITION*)telegram.Extrainfo;
		std::cout << "Monster Move! [ " << telegram.Receiver << "] - " << pos->x << " " << pos->y << std::endl;
		delete telegram.Extrainfo;
	}
	return true;
	case MESSAGE_TYPE::Msg_objectChangeState:
	{
		std::cout << "Monster Change State! [ " << telegram.Receiver << "] - " << (char*)telegram.Extrainfo << std::endl;
		delete telegram.Extrainfo;
	}
	return true;
	default:
		break;
	}

	return false;
}

POSITION CMonster::CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension)
{
	POSITION Result;

	float t2 = t * t;
	float t3 = t2 * t;

	float B0 = (-t3 + 2.0 * t2 - t) * (tension);
	float B1 = 1.0 + (tension - 3) * t2 + (2 - tension) * t3;
	float B2 = tension * t + (3 - 2 * tension) * t2 + (tension - 2) * t3;
	float B3 = (t3 - t2) * (tension);

	Result.x = (B0 * P0.x + B1 * P1.x + B2 * P2.x + B3 * P3.x);
	Result.y = (B0 * P0.y + B1 * P1.y + B2 * P2.y + B3 * P3.y);

	return Result;
}
