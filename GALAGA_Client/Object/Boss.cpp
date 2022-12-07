#include "Boss.h"

CBoss::CBoss()
{

}

CBoss::~CBoss()
{

}

bool CBoss::Init(POSITION LTpos, const OBJECT_TYPE& type, POSITION Vector, int stageNum)
{
	float AttackRate = 0.0f;
	switch (stageNum)
	{
	case 1:
		AttackRate = 2.0f;
		break;
	case 2:
		AttackRate = 3.45f;
		break;
	case 3:
		AttackRate = 5.5f;
		break;

	default:
		break;
	}

	switch (type)
	{
	case OBJECT_TYPE::OBJ_BOSS_ONE:
		CObject::Init(L"../Image/Terran_img/Battle Cruiser.png", LTpos, Vector, { 100,120 }, 20000.0f * AttackRate, { 74,75 }, { 1, 57 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_BOSS_TWO:
		CObject::Init(L"../Image/Protoss_img/mothership.png", LTpos, Vector, { 100,100 }, 40000.0f * AttackRate, { 67 , 62 }, { 23 ,18 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_BOSS_THREE:
		CObject::Init(L"../Image/Zerg_img/Guardian.png", LTpos, Vector, { 120,100 }, 65000.0f, { 70  , 40 }, { 650  ,85 }, PLAYER_TYPE::PT_MONSTER);
		break;
	default:
		break;
	}


	return true;
}

void CBoss::Update(float fDeltaTime)
{
	CMonster::Update(fDeltaTime);
}


bool CBoss::HandleMessage(const Telegram& telegram)
{
	CMonster::HandleMessage(telegram);
	/*MESSAGE_TYPE msg_type = (MESSAGE_TYPE)telegram.Msg;

	switch (msg_type)
	{
	case MESSAGE_TYPE::Msg_objectMove:
	{
		POSITION* pos = (POSITION*)telegram.Extrainfo;
		std::cout << "Boss Move! [ " << telegram.Receiver << "] - " << pos->x << " " << pos->y << std::endl;
		delete telegram.Extrainfo;
	}
	return true;
	case MESSAGE_TYPE::Msg_objectChangeState:
	{
		std::cout << "Boss Change State! [ " << telegram.Receiver << "] - " << (char*)telegram.Extrainfo << std::endl;
		delete telegram.Extrainfo;
	}
	return true;
	default:
		break;
	}*/

	return false;
}