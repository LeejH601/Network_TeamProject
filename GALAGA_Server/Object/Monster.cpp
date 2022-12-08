#include "../Network/NetworkDevice.h"
#include "../Core.h"
#include "../Locator.h"
#include "Monster.h"
#include "BulletList.h"
#include "../Core/Timer.h"
#include <math.h>




CMonster::CMonster()
{

}

CMonster::~CMonster()
{

}

bool CMonster::Init(POSITION LTpos, const MONSTER_PATTERN& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum)
{

	//if (m_Explode_img == NULL)
	//{
	//	m_Explode_img.Load(TEXT("./Image/Scene_Back_img/Explode(2).png"));
	//	m_Explode_img_LT = { 0,0 };
	//	m_Explode_img_Size = { 256,200 };

	//}


	float AttackRate = 0.0f;
	switch (StageNum)
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

	fire_delay = 0.7f;
	fire_rate = fire_delay;

	SetObjType(type);

	if (type == OBJECT_TYPE::OBJ_Vessel)
		CObject::Init(LTpos, Vector, { 80,80 }, 2000.0f * AttackRate, PLAYER_TYPE::PT_MONSTER);
	else
		CObject::Init(LTpos, Vector, { 40,40 }, 100.0f * AttackRate, PLAYER_TYPE::PT_MONSTER);


	MONSTER_PATTERN Pattern = pattern;
	//Pattern = MONSTER_PATTERN::PAT_STAIRS;

	RESOLUTION Resol = CCore::GetInst()->GetResolution();
	POSITION Resolution{ (float)Resol.iW, (float)Resol.iH };

	switch (Pattern)
	{
	case MONSTER_PATTERN::PAT_STRAIGHT:
	{
		m_Path.SetTension(0.0f);
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION end{ start.x , Resolution.y + 100 };

		m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
		m_Path.AddPoint(start);
		for (int i = 0; i < 6; ++i) {
			m_Path.AddPoint(POSITION(start.x, start.y + ((end.y - start.y) / 6 * (i + 1))));
		}
		m_Path.AddPoint(end);


		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(POSITION(end.x, end.y + (i * 1) * 50.0f));
	}
	break;
	case MONSTER_PATTERN::PAT_STAIR_LEFT:
	case MONSTER_PATTERN::PAT_STAIR_RIGHT:
	{
		POSITION start, p0, p1, p2, p3, p4, p5, end;

		if (pattern == MONSTER_PATTERN::PAT_STAIR_LEFT)
		{
			start = POSITION{ Resolution.x / 4, -50 };
			p0 = POSITION{ start.x, 100 };
			p1 = POSITION{ start.x * 3, 100 };
			p2 = POSITION{ p1.x , p1.y + 200 };
			p3 = POSITION{ p0.x, p2.y };
			p4 = POSITION{ p3.x , p3.y + 200 };
			p5 = POSITION{ p1.x , p4.y };
			end = POSITION{ start.x * 3,  Resolution.y + 100 };
		}
		else {
			start = POSITION{ Resolution.x - Resolution.x / 4, -50 };
			p0 = POSITION{ start.x, 100 };
			p1 = POSITION{ (Resolution.x - start.x), 100 };
			p2 = POSITION{ p1.x , p1.y + 200 };
			p3 = POSITION{ p0.x, p2.y };
			p4 = POSITION{ p3.x , p3.y + 200 };
			p5 = POSITION{ p1.x , p4.y };
			end = POSITION{ start.x,  Resolution.y + 100 };
		}

		m_Path.SetTension(0.0f);


		m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(p1);
		m_Path.AddPoint(p2);
		m_Path.AddPoint(p3);
		m_Path.AddPoint(p4);
		m_Path.AddPoint(p5);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(POSITION(end.x, end.y + (i * 1) * 50.0f));
	}
	break;
	case MONSTER_PATTERN::PAT_RING:
	{
		m_Path.SetTension(0.5f);
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION p0{ start.x, Resolution.y / 4 + 50 };
		POSITION p1{ Resolution.x / 2, Resolution.y / 2 + 50 };
		POSITION p2{ Resolution.x - start.x, Resolution.y / 4 + 50 };
		POSITION p3{ p1.x,Resolution.y / 8 + 50 };
		POSITION end{ p2.x, -50 };

		m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(p1);
		m_Path.AddPoint(p2);
		m_Path.AddPoint(p3);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(p1);
		m_Path.AddPoint(p2);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(POSITION(end.x, end.y - (i * 1) * 50.0f));
	}
	break;
	case MONSTER_PATTERN::PAT_UTURN:
	{
		m_Path.SetTension(0.3f);
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION p0{ Resolution.x / 2, Resolution.y / 2 };
		POSITION end{ Resolution.x - start.x, -50 };

		m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(POSITION(end.x, end.y - (i * 1) * 50.0f));
	}
	break;
	case MONSTER_PATTERN::PAT_CROSS:
	{
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
	}
	break;
	default:
		break;
	}
	//m_Path.CalculUniformPos();
	return true;
}

bool CMonster::Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType)
{
	//MONSTER_PATTERN Pattern = (MONSTER_PATTERN)(rand() % (int)MONSTER_PATTERN::END_ENUM);

	//RESOLUTION Resol = CCore::GetInst()->GetResolution();
	//POSITION Resolution{ (float)Resol.iW, (float)Resol.iH };

	//switch (Pattern)
	//{
	//case MONSTER_PATTERN::PAT_STRAIGHT:
	//{
	//	m_Path.SetTension(0.0f);
	//	POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
	//	POSITION end{ start.x , Resolution.y + 100 };

	//	m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
	//	m_Path.AddPoint(start);
	//	m_Path.AddPoint(end);

	//	for (int i = 0; i < 3; ++i)
	//		m_Path.AddPoint(POSITION(end.x, end.y + 50.0f * (i + 1)));
	//}
	//break;
	//case MONSTER_PATTERN::PAT_STAIRS:
	//{
	//	m_Path.SetTension(0.0f);

	//	POSITION start{ Resolution.x / 4, -50 };
	//	POSITION p0{ start.x, 100 };
	//	POSITION p1{ start.x * 3, 100 };
	//	POSITION end{ start.x * 3,  Resolution.y + 100 };

	//	m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
	//	m_Path.AddPoint(start);
	//	m_Path.AddPoint(p0);
	//	m_Path.AddPoint(p1);
	//	m_Path.AddPoint(end);

	//	for (int i = 0; i < 3; ++i)
	//		m_Path.AddPoint(end);
	//}
	//break;
	//case MONSTER_PATTERN::PAT_RING:
	//{
	//	m_Path.SetTension(0.5f);
	//	POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
	//	POSITION p0{ start.x, Resolution.y / 4 + 50 };
	//	POSITION p1{ Resolution.x / 2, Resolution.y / 2 + 50 };
	//	POSITION p2{ Resolution.x - start.x, Resolution.y / 4 + 50 };
	//	POSITION p3{ p1.x,Resolution.y / 4 + 50 };
	//	POSITION end{ p2.x, -50 };

	//	m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
	//	m_Path.AddPoint(start);
	//	m_Path.AddPoint(p0);
	//	m_Path.AddPoint(p1);
	//	m_Path.AddPoint(p2);
	//	m_Path.AddPoint(p3);
	//	m_Path.AddPoint(p0);
	//	m_Path.AddPoint(p1);
	//	m_Path.AddPoint(p2);
	//	m_Path.AddPoint(end);

	//	for (int i = 0; i < 3; ++i)
	//		m_Path.AddPoint(end);
	//}
	//break;
	//case MONSTER_PATTERN::PAT_UTURN:
	//{
	//	m_Path.SetTension(0.3f);
	//	POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
	//	POSITION p0{ Resolution.x / 2, Resolution.y / 2 };
	//	POSITION end{ Resolution.x - start.x, -50 };

	//	m_Path.AddPoint(POSITION(start.x, start.y - 10.0f));
	//	m_Path.AddPoint(start);
	//	m_Path.AddPoint(p0);
	//	m_Path.AddPoint(end);

	//	for (int i = 0; i < 3; ++i)
	//		m_Path.AddPoint(end);
	//}
	//break;
	//case MONSTER_PATTERN::PAT_CROSS:
	//{
	//	POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
	//}
	//break;
	//default:
	//	break;
	//}
	////m_Path.CalculUniformPos();

	//return CObject::Init(LTpos, Vector, Size, HP, obType);
	return false;
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

void CMonster::CreateBullet(CBulletList* _bulletList)
{
	if (rand() % 2 == 1) {
		CPlayer* player = Locator.GetPlayer(rand() % 2);
		POSITION b_vector = (player->GetPos() + (player->GetSize() / 3)) - CObject::GetPos();
		b_vector = b_vector / (sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y));

		//std::cout << "bullet" << std::endl;

		(_bulletList)->AddBullet(CObject::GetPos(), { 15,15 }, b_vector, float(rand() % 200) + 50.f);
		(_bulletList)->SetAttack(50.0f);
	}

	fire_delay = fire_rate;

	//if (rand() % 2 == 1) {
	//	POSITION b_vector = CObject::GetPos();
	//	if (rand() % 3 == 1) {
	//		CPlayer* player = CSceneManager::GetInst()->GetPlayer();
	//		b_vector = (player->GetPos() + (player->GetSize() / 3)) - CObject::GetPos();
	//	}
	//	else {
	//		b_vector.x = 0;
	//	}
	//	b_vector = b_vector / (sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y));
	//	//printf("b_vector = (%f, %f)\n", b_vector.x, b_vector.y);
	//	_bulletList
	//	(*_bulletList)->PushBack(CObject::GetPos(), { 15,15 }, b_vector, float(rand() % 200) + B_speed);
	//	// ���� �Ѿ��� ���ݷ��� 50���� �����մϴ�...
	//	(*_bulletList)->SetAttack(50.0f);


	//}
}

void CMonster::Input(float fDeltaTime)
{
}

void CMonster::Update(float fDeltaTime)
{
	/*if (m_bDie == true)
		return;*/

	fire_delay -= (fDeltaTime);

	m_Path.Update(fDeltaTime * 2.0f);
	SetPos(m_Path.GetNextPos());

	if (m_Path.GetPathEnd()) {
		SetState(OBJECT_STATE::ERASE); // 수정 해야할 수도?
		//SendMsgChangeState(OBJECT_STATE::DESTORY);
	}

	CObject::Update(fDeltaTime);


}

void CMonster::LateUpdate(float fDeltaTime)
{
}

bool CMonster::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return true;
}
