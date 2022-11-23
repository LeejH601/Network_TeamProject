#include "../Network/NetworkDevice.h"
#include "../Core.h"
#include "../Locator.h"
#include "Monster.h"
#include "BulletList.h"
#include "../Core/Timer.h"
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
	float length = 0.0f;
	float total_len = 0.0f;
	for (int i = 0; i < m_points.size() - 1 - 3; ++i) {

		if (length < FLT_EPSILON)
			points.push_back(m_points[i]);
		else {
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (length / total_len), m_ftension));
		}

		POSITION dist = m_points[i + 1] - m_points[i];
		total_len = dist.x * dist.x + dist.y * dist.y;
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

CMonster::~CMonster()
{

}

bool CMonster::Init(POSITION LTpos, const Pattern& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum)
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

	fire_delay = 1000.0f;
	fire_rate = 1000.0f;

	if(type == OBJECT_TYPE::OBJ_Vessel)
		CObject::Init(LTpos, Vector, { 80,80 }, 2000.0f * AttackRate, PLAYER_TYPE::PT_MONSTER);
	else
		CObject::Init(LTpos, Vector, { 40,40 }, 100.0f * AttackRate, PLAYER_TYPE::PT_MONSTER);

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

	//	m_Path.AddPoint(start);
	//	m_Path.AddPoint(end);

	//	for (int i = 0; i < 3; ++i)
	//		m_Path.AddPoint(end);
	//}
	//break;
	//case MONSTER_PATTERN::PAT_STAIRS:
	//{
	//	m_Path.SetTension(0.0f);

	//	POSITION start{ Resolution.x / 4, -50 };
	//	POSITION p0{ start.x, 100 };
	//	POSITION p1{ start.x * 3, 100 };
	//	POSITION end{ start.x * 3,  Resolution.y + 100 };

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

	Msg_Create(type, LTpos);
	return true;
}

void CMonster::Msg_Create(OBJECT_TYPE TYPE, POSITION POS)
{
	// Monster Create Message
	Telegram telegram;
	telegram.Sender = m_iObjID;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	telegram.DispatchTime = CTimer::GetInst()->GetTime();
	telegram.Extrainfo = new char[sizeof(int) + sizeof(POSITION)];
	memcpy(telegram.Extrainfo, &TYPE, sizeof(int));
	memcpy((char*)telegram.Extrainfo + sizeof(int), &POS, sizeof(POSITION));

	CObject::SendMessageToClient(telegram);

	/*CNetworkDevice* p;
	if (!CCore::GetInst()->m_hPlayer2)
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
	else
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);

	p->AddMessage(telegram);
	LeaveCriticalSection(&cs);*/
}

void CMonster::Msg_Move(POSITION POS)
{
	Telegram telegram;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
	telegram.Extrainfo = new char[sizeof(POSITION)];
	memcpy(telegram.Extrainfo, &POS, sizeof(POSITION));

	auto cs = client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second;
	EnterCriticalSection(&cs);
	CNetworkDevice* p;
	if (!CCore::GetInst()->m_hPlayer2)
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
	else
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);

	p->AddMessage(telegram);
	LeaveCriticalSection(&cs);
}


bool CMonster::Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType)
{
	MONSTER_PATTERN Pattern = (MONSTER_PATTERN)(rand() % (int)MONSTER_PATTERN::END_ENUM);

	RESOLUTION Resol = CCore::GetInst()->GetResolution();
	POSITION Resolution{ (float)Resol.iW, (float)Resol.iH };

	switch (Pattern)
	{
	case MONSTER_PATTERN::PAT_STRAIGHT:
	{
		m_Path.SetTension(0.0f);
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION end{ start.x , Resolution.y + 100 };

		m_Path.AddPoint(start);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(end);
	}
	break;
	case MONSTER_PATTERN::PAT_STAIRS:
	{
		m_Path.SetTension(0.0f);

		POSITION start{ Resolution.x / 4, -50 };
		POSITION p0{ start.x, 100 };
		POSITION p1{ start.x * 3, 100 };
		POSITION end{ start.x * 3,  Resolution.y + 100 };

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
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION p0{ start.x, Resolution.y / 4 + 50 };
		POSITION p1{ Resolution.x / 2, Resolution.y / 2 + 50 };
		POSITION p2{ Resolution.x - start.x, Resolution.y / 4 + 50 };
		POSITION p3{ p1.x,Resolution.y / 4 + 50 };
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
		POSITION start{ Resolution.x / 4 + rand() % (int)(Resolution.x / 2), -50 };
		POSITION p0{ Resolution.x / 2, Resolution.y / 2 };
		POSITION end{ Resolution.x - start.x, -50 };

		m_Path.AddPoint(start);
		m_Path.AddPoint(p0);
		m_Path.AddPoint(end);

		for (int i = 0; i < 3; ++i)
			m_Path.AddPoint(end);
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

	return CObject::Init(LTpos, Vector, Size, HP, obType);
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

void CMonster::CreateBullet(CBulletList** _bulletList)
{
	if (rand() % 2 == 1) {
		POSITION b_vector = CObject::GetPos();

		(*_bulletList)->AddBullet(CObject::GetPos(), { 15,15 }, b_vector, float(rand() % 200) + 50.f);
		(*_bulletList)->SetAttack(50.0f);
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
	if (m_bDie == true)
		return;

	fire_delay -= (fDeltaTime * 300.0f);

	/*m_Path.Update(fDeltaTime);
	SetPos(m_Path.GetNextPos());

	CObject::Update(fDeltaTime);*/

	//if (m_state != MONSTER_STATE::DESTORY) {
	//	switch (mPattern) // ������Ʈ�� ������ ���Ͽ� �°� ��ġ�� ������Ʈ
	//	{
	//	case Pattern::SIN:
	//	{
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (update_count < 0.0f) {
	//				POSITION _vector = CObject::GetVector();
	//				POSITION n_vector = { _vector.y, -_vector.x };			// ���� ���� ���� ���� 
	//				if (bias == 0)
	//					n_vector = n_vector * (-1);
	//				float det = sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y);	// ���������� ũ�⸦ ���Ѵ�...
	//				_vector = _vector + (n_vector / ceta);									// 
	//				det = sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
	//				/*printf("%f\n", sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y));
	//				POSITION t_vector = n_vector / 45;
	//				printf("%f\n", sqrt(t_vector.x * t_vector.x + t_vector.y * t_vector.y));
	//				printf("tangent : %f\n", sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y) / sqrt(_vector.x * _vector.x + _vector.y * _vector.y));*/
	//				_vector = _vector / det;
	//				CObject::SetVector(_vector);
	//				/*if (ceta < 20)
	//					ceta -= (c_det * 0.2f);
	//				else
	//				ceta -= c_det;
	//				if (ceta < 2 || ceta > 89) {
	//					c_det = -c_det;
	//				}*/
	//				t_count -= fDeltaTime;
	//				if (t_count <= 0.0f) {
	//					t_speed *= 2.0f;
	//					ceta = 5;
	//				}
	//				else if (t_count <= 1.0f) {
	//					t_speed /= 2.0f;
	//					ceta = 90;
	//				}
	//				update_count = 0.3f;
	//				//	printf("���� ��ġ : (%f, %f) ---- ���� : (%f, %f) ---- ceta = %f ----- t_speed = %d\n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, ceta, t_count);

	//			}
	//			else
	//				update_count -= fDeltaTime;

	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}
	//	}
	//	break;
	//	case Pattern::SIN2:
	//	{
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (update_count < 0.0f) {
	//				POSITION _vector = CObject::GetVector();
	//				POSITION n_vector = { _vector.y, -_vector.x };
	//				if (bias == 0)
	//					n_vector = n_vector * (-1);
	//				float det = sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y);
	//				_vector = _vector + (n_vector / (45 - (45 * (CObject::GetPos().y / 500))));
	//				det = sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
	//				_vector = _vector / det;
	//				CObject::SetVector(_vector);
	//				d_count += fDeltaTime;
	//				update_count = t_count;
	//				t_count -= c_det;
	//				if (t_count <= 0.0f || t_count >= 3.0f) {
	//					c_det = -c_det;
	//				}
	//				//	printf("���� ��ġ : (%f, %f) ---- ���� : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

	//			}
	//			else
	//				update_count -= fDeltaTime;
	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}

	//	}
	//	break;
	//	case Pattern::SIN3:
	//	{
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (update_count < 0.0f) {
	//				POSITION _vector = CObject::GetVector();
	//				POSITION n_vector = { _vector.y, -_vector.x };
	//				if (bias == 0)
	//					n_vector = n_vector * (-1);
	//				if (!d_triger)
	//					n_vector = n_vector * (-1);
	//				float det = sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y);
	//				_vector = n_vector;
	//				_vector = _vector / det;
	//				CObject::SetVector(_vector);
	//				update_count -= fDeltaTime;
	//				if (count < 0.0f) {
	//					count = 2.0f;
	//					d_triger = !d_triger;
	//				}
	//				//	printf("���� ��ġ : (%f, %f) ---- ���� : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

	//			}
	//			else
	//				update_count -= fDeltaTime;
	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}
	//	}
	//	break;
	//	case Pattern::SIN4:
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}
	//		break;
	//	case Pattern::SIN5:
	//	{
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (update_count < 0.0f) {
	//				POSITION _vector = CObject::GetVector();
	//				POSITION n_vector = { _vector.y, -_vector.x };
	//				if (bias == 0)
	//					n_vector = n_vector * (-1);
	//				float det = sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y);
	//				_vector = _vector + (n_vector / (5));
	//				det = sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
	//				_vector = _vector / det;
	//				CObject::SetVector(_vector);
	//				d_count += fDeltaTime;
	//				update_count = t_count;
	//				t_count -= c_det;

	//				//	printf("���� ��ġ : (%f, %f) ---- ���� : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

	//			}
	//			else
	//				update_count -= fDeltaTime;
	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}

	//	}
	//	break;
	//	case Pattern::SIN6:
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//		}
	//		else {
	//			if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//				if (m_state != MONSTER_STATE::DONDESTORY)
	//					m_state = MONSTER_STATE::DESTORY;
	//			}
	//		}
	//		break;
	//	case Pattern::SIN7:
	//		if (m_state != MONSTER_STATE::WAIT) {
	//			if (m_state == MONSTER_STATE::DONDESTORY && CObject::GetPos().y < 700 && CObject::GetPos().y > 0)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (CObject::GetPos().y < 400) {
	//				float fMovedIstance = 0.00166666f;
	//				POSITION r_vector = CObject::GetPos() + (CObject::GetVector() * fMovedIstance) * t_speed;
	//				CObject::SetPos(r_vector);
	//			}
	//			else {
	//				if (m_state != MONSTER_STATE::WAIT)
	//					m_state = MONSTER_STATE::WAIT;
	//			}
	//		}
	//		else {
	//			/*	if (!(m_tLTPos.y > -200 && m_tLTPos.y < 1000 && m_tLTPos.x > -200 && m_tLTPos.y < 800)) {
	//					if (m_state != MONSTER_STATE::DONDESTORY)
	//						m_state = MONSTER_STATE::DESTORY;
	//				}*/
	//		}
	//		break;
	//	default:
	//		break;
	//	}

	//	if (mPattern != Pattern::SIN7) {
	//		float fMovedIstance = 0.00166666f;
	//		//float fMovedIstance = 0.0022222f;
	//		POSITION r_vector = CObject::GetPos() + (CObject::GetVector() * fMovedIstance) * t_speed;
	//		CObject::SetPos(r_vector);
	//	}


		//fire_delay--; 
	//}
}

void CMonster::LateUpdate(float fDeltaTime)
{
}

bool CMonster::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return true;
}
