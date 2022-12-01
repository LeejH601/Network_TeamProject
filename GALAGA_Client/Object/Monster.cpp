#include	"Monster.h"
#include	"BulletList.h"
#include	"..\Core.h"

void CPath::Update(float fDeltaTime)
{
	if (m_iIndex < m_points.size() - 4) {
		m_ft += fDeltaTime;
		while (m_ft >= 1.0f) {
			m_ft -= 1.0f;
			m_iIndex++;
		}
	}
}

POSITION CPath::GetNextPos()
{
	return CardinalSpline(m_points[m_iIndex], m_points[m_iIndex + 1], m_points[m_iIndex + 2], m_points[m_iIndex + 3], m_ft, m_ftension);
}

void CPath::CalculUniformPos()
{
	float detT = 40.0f;
	std::vector<POSITION> points;
	float length = 0.0f;
	float total_len = 0.0f;
	for (int i = 0; i < m_points.size() - 1 - 3; ++i) {

		//if (length < FLT_EPSILON)
		points.push_back(m_points[i + 1]);
		/*else {
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (length / total_len), m_ftension));
		}*/

		POSITION dist = m_points[i + 2] - m_points[i + 1];
		total_len = sqrt(dist.x * dist.x + dist.y * dist.y);
		length = total_len;

		while (length > detT)
		{
			length -= detT;
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (1 - (length / total_len)), m_ftension));
		}
	}

	m_points = points;
}

POSITION CPath::CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension)
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



CMonster::CMonster()
{

}

CMonster::CMonster(const CMonster& player)
{
}

void CMonster::Run(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	Update(fDeltaTime);
	LateUpdate(fDeltaTime);
	Render(mainhDC, hdc, fDeltaTime);
}


bool CMonster::Init(POSITION LTpos, const MONSTER_PATTERN& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum)
{

	if (m_Explode_img == NULL)
	{
		m_Explode_img.Load(TEXT("../Image/Scene_Back_img/Explode(2).png"));
		m_Explode_img_LT = { 0,0 };
		m_Explode_img_Size = { 256,200 };

	}

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

	fire_rate = 3000;
	switch (type) // 타입에 따라 이미지를 로드
	{
	case OBJECT_TYPE::OBJ_Wraith:
		CObject::Init(L"../Image/Terran_img/Wraith.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 46,41 }, { 15 * 46, 0 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Valkyrie:
		CObject::Init(L"../Image/Terran_img/Valkyrie.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 106,102 }, { 1, 1 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Battlecruiser:
		CObject::Init(L"../Image/Terran_img/Battle Cruiser.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 73,73 }, { 1,56 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Dropship:
		CObject::Init(L"../Image/Terran_img/Dropship.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 89,80 }, { 2, 0 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Vessel:
		CObject::Init(L"../Image/Terran_img/Vessel.png", LTpos, Vector, { 80,80 }, 2000.0f * AttackRate, { 203,158 }, { 5, 5 }, PLAYER_TYPE::PT_MONSTER);
		break;

	case OBJECT_TYPE::OBJ_Mutalisk:
		CObject::Init(L"../Image/Zerg_img/Mutalisk.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 59 , 49 }, { 539 ,13 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Queen:
		CObject::Init(L"../Image/Zerg_img/Queen.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 45 , 46 }, { 636 ,14 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Scourge:
		CObject::Init(L"../Image/Zerg_img/Scourge.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 22 , 17 }, { 277 ,8 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Devourer:
		CObject::Init(L"../Image/Zerg_img/Devourer.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 48 , 64 }, { 597 ,105 }, PLAYER_TYPE::PT_MONSTER);
		break;

	case OBJECT_TYPE::OBJ_Scout:
		CObject::Init(L"../Image/Protoss_img/scout.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 23 , 31 }, { 9 ,12 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Arbiter:
		CObject::Init(L"../Image/Protoss_img/Archon.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 63 , 70 }, { 1672 ,112 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Carrier:
		CObject::Init(L"../Image/Protoss_img/carrier.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 35 , 47 }, { 5 ,9 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_Corsair:
		CObject::Init(L"../Image/Protoss_img/mothership.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 67 , 62 }, { 23 ,18 }, PLAYER_TYPE::PT_MONSTER);
		break;
	default:
		break;
	}
	bias = (LTpos.x > 400) ? 0 : 1;

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

	return true;
}

void CMonster::Input(float fDeltaTime)
{
}

void CMonster::Update(float fDeltaTime)
{
	if (m_bDie == true)
		return;

	m_Path.Update(fDeltaTime * 2.0f);
	SetPos(m_Path.GetNextPos());

	CObject::Update(fDeltaTime);
}

void CMonster::LateUpdate(float fDeltaTime)
{
}

void CMonster::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{

	if (m_bDie == true)
	{
		RenderExplode(mainhDC, hdc, fDeltaTime);
	}
	else
		CObject::Render(mainhDC, hdc, fDeltaTime);


}

void CMonster::RenderExplode(HDC mainhDC, HDC hdc, float fDeltaTime)
{

	m_Explode_img_Count += 1;

	m_Explode_img.Draw(hdc, CObject::m_tLTPos.x - (CObject::m_tSize.x / 2), CObject::m_tLTPos.y - (CObject::m_tSize.y / 2),
		CObject::m_tSize.x + (CObject::m_tSize.x / 2), CObject::m_tSize.y + (CObject::m_tSize.y / 2),
		m_Explode_img_LT.x, m_Explode_img_LT.y, m_Explode_img_Size.x, m_Explode_img_Size.y);

	if (m_Explode_img_Count % 30 == 0)
	{
		m_Explode_img_LT.x = m_Explode_img_LT.x + m_Explode_img_Size.x;

	}
	if (m_Explode_img_Count % (30 * 4) == 0)
	{
		m_Explode_img_LT.x = 5;
		m_Explode_img_LT.y = m_Explode_img_LT.y + m_Explode_img_Size.y;
	}

	// 출력이미지를 전부 출력했을 때 몬스터를 삭제합니다... 
	/*if (m_Explode_img_Count == 300)
		m_state = OBJECT_STATE::DESTORY;*/

}

bool CMonster::HandleMessage(const Telegram& msg)
{
	//switch ((MESSAGE_TYPE)msg.Msg)
	//{
	//case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position 
	//{
	//	int ObjectType;
	//	POSITION Position;
	//	memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
	//	memcpy(&Position, (char*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
	//	return true;
	//}
	//case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
	//{
	//	int ObjectState;
	//	memcpy(&ObjectState, msg.Extrainfo, sizeof(int));
	//	return true;
	//}
	//default:
	//	break;
	//}
	CObject::HandleMessage(msg);

	return false;
}

