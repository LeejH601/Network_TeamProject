#include "Monster.h"
#include "..\Core.h"
#include <math.h>


void CPath::Update(float fDeltaTime)
{
	if (m_iIndex < m_points.size() - 3) {
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
	float detT = pow(20.0f, 2);
	std::vector<POSITION> points;
	bool flag = true;
	float length = 0.0f;
	for (int i = 0; i < m_points.size() - 1 - 3; ++i) {

		POSITION dist = m_points[i + 1] - m_points[i];
		float total_len = dist.x * dist.x + dist.y * dist.y;
		length = total_len;

		if (length < FLT_EPSILON)
			points.push_back(m_points[i]);
		else {
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (detT - length / total_len), m_ftension));
		}

		while (length > detT)
		{
			length -= detT;
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (1 - (length / total_len)), m_ftension));
		}

		flag = true;
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

CMonster::~CMonster()
{

}


bool CMonster::Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType)
{
	MONSTER_PATTERN Pattern = (MONSTER_PATTERN)(rand() % (int)MONSTER_PATTERN::END_ENUM);

	RESOLUTION Resolution = CCore::GetInst()->GetResolution();

	switch (Pattern)
	{
	case MONSTER_PATTERN::PAT_STRAIGHT:
	{
		m_Path.SetTension(0.0f);
		POSITION start{ Resolution.iW / 4 + rand() % (Resolution.iW / 2), -50 };
		POSITION end{ start.x , Resolution.iH + 100 };

		m_Path.AddPoint(start);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(end);
	}
	break;
	case MONSTER_PATTERN::PAT_STAIRS:
	{
		m_Path.SetTension(0.0f);

		POSITION start{ Resolution.iW / 4, -50 };
		POSITION p0{ start.x, 100 };
		POSITION p1{ start.x * 3, 100 };
		POSITION end{ start.x * 3,  Resolution.iH + 100 };

		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(p1);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(end);
	}
	break;
	case MONSTER_PATTERN::PAT_RING:
	{
		m_Path.SetTension(0.5f);
		POSITION start{ Resolution.iW / 4 + rand() % (Resolution.iW / 2), -50 };
		POSITION p0{ start.x, Resolution.iH / 4 + 50 };
		POSITION p1{ Resolution.iW / 2, Resolution.iH / 2 + 50 };
		POSITION p2{ Resolution.iW - start.x, Resolution.iH / 4 + 50 };
		POSITION p3{ p1.x,Resolution.iH / 4 + 50 };
		POSITION end{ p2.x, -50 };

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
			m_Path.AddPoint(end);
	}
	break;
	case MONSTER_PATTERN::PAT_UTURN:
	{
		m_Path.SetTension(0.3f);
		POSITION start{ Resolution.iW / 4 + rand() % (Resolution.iW / 2), -50 };
		POSITION p0{ Resolution.iW / 2, Resolution.iH / 2 };
		POSITION end{ Resolution.iW - start.x, -50 };

		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(end);
	}
	break;
	case MONSTER_PATTERN::PAT_CROSS:
		POSITION start{ Resolution.iW / 4 + rand() % (Resolution.iW / 2), -50 };
		break;
	default:
		break;
	}
	m_Path.CalculUniformPos();

	CObject::Init(LTpos, Vector, Size, HP, obType);
}

void CMonster::Update(float fDeltaTime)
{
	m_Path.Update(fDeltaTime);
	SetPos(m_Path.GetNextPos());

	CObject::Update(fDeltaTime);
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


