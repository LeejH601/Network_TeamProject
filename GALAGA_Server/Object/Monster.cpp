#include "../Network/NetworkDevice.h"
#include "../Core.h"
#include "../Locator.h"
#include "Monster.h"
#include "BulletList.h""

CMonster::CMonster()
{

}

CMonster::~CMonster()
{

}

bool CMonster::Init(POSITION LTpos, const Pattern& pattern, const Monster_type& type, POSITION Vector, int StageNum)
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

	fire_rate = 3000;
	switch (type) // 타입에 따라 이미지를 로드
	{
	case Monster_type::Wraith:
		CObject::Init(L"./Image/Terran_img/Wraith.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 46,41 }, { 15 * 46, 0 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Valkyrie:
		CObject::Init(L"./Image/Terran_img/Valkyrie.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 106,102 }, { 1, 1 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Battlecruiser:
		CObject::Init(L"./Image/Terran_img/Battle Cruiser.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 73,73 }, { 1,56 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Dropship:
		CObject::Init(L"./Image/Terran_img/Dropship.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 89,80 }, { 2, 0 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Vessel:
		CObject::Init(L"./Image/Terran_img/Vessel.png", LTpos, Vector, { 80,80 }, 2000.0f * AttackRate, { 203,158 }, { 5, 5 }, PLAYER_TYPE::PT_MONSTER);
		break;

	case Monster_type::Mutalisk:
		CObject::Init(L"./Image/Zerg_img/Mutalisk.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 59 , 49 }, { 539 ,13 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Queen:
		CObject::Init(L"./Image/Zerg_img/Queen.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 45 , 46 }, { 636 ,14 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Scourge:
		CObject::Init(L"./Image/Zerg_img/Scourge.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 22 , 17 }, { 277 ,8 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Devourer:
		CObject::Init(L"./Image/Zerg_img/Devourer.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 48 , 64 }, { 597 ,105 }, PLAYER_TYPE::PT_MONSTER);
		break;

	case Monster_type::Scout:
		CObject::Init(L"./Image/Protoss_img/scout.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 23 , 31 }, { 9 ,12 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Arbiter:
		CObject::Init(L"./Image/Protoss_img/Archon.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 63 , 70 }, { 1672 ,112 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Carrier:
		CObject::Init(L"./Image/Protoss_img/carrier.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 35 , 47 }, { 5 ,9 }, PLAYER_TYPE::PT_MONSTER);
		break;
	case Monster_type::Corsair:
		CObject::Init(L"./Image/Protoss_img/mothership.png", LTpos, Vector, { 40,40 }, 100.0f * AttackRate, { 67 , 62 }, { 23 ,18 }, PLAYER_TYPE::PT_MONSTER);
		break;
	default:
		break;
	}
	bias = (LTpos.x > 400) ? 0 : 1;
	mPattern = pattern;
	switch (mPattern) // 패턴 타입에 따라 초기화 시행
	{
	case Pattern::SIN:
		update_count = 1.0f;
		t_speed = 300.0f;
		t_count = 500 / t_speed;
		ceta = 90;
		d_count = 0;
		c_det = 1;

		fire_delay = fire_rate;

		break;
	case Pattern::SIN2:
		t_count = 0.2f;
		t_speed = 500.0f;
		ceta = 45;
		d_count = 0;
		c_det = 2;

		fire_delay = 1000;

		break;
	case Pattern::SIN3:
		t_count = 0.5f;
		update_count = 3.0f;
		t_speed = 500.0f;
		ceta = 45;
		d_count = 0;
		c_det = 2;

		fire_delay = 500;

		break;
	case Pattern::SIN4:
		t_count = 0.5f;
		t_speed = 600.0f;
		ceta = 45;
		d_count = 0;
		c_det = 2;

		fire_delay = 200;

		break;
	case Pattern::SIN5:
		t_count = 0.5f;
		t_speed = 500.0f;
		ceta = 45;
		d_count = 0;
		c_det = 2;

		fire_delay = 200;

		break;
	case Pattern::SIN6:
		t_speed = 200.0f;

		fire_delay = 300;
		break;
	case Pattern::SIN7:
		t_speed = 300.0f;

		fire_rate = 1000000000;
		fire_delay = fire_rate;
		break;
	default:
		break;
	}

	Msg_Create(type, LTpos);
	return true;
}

void CMonster::Msg_Create(Monster_type TYPE, POSITION POS)
{
	int ObjectEnum = 0;
	Telegram telegram;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	telegram.Extrainfo = new char[sizeof(int) + sizeof(POSITION) + sizeof(int)];
	memcpy(telegram.Extrainfo, &TYPE, sizeof(int));
	memcpy((char*)telegram.Extrainfo + sizeof(int), &POS, sizeof(POSITION));
	memcpy((char*)telegram.Extrainfo + sizeof(int) + sizeof(POSITION), &ObjectEnum, sizeof(int));

	CNetworkDevice* p;
	if (!CCore::GetInst()->m_hPlayer2)
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
	else
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);

	p->AddMessage(telegram);
	LeaveCriticalSection(&cs);
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
		// 몬스터 총알의 공격력을 50으로 설정합니다...
		(*_bulletList)->SetAttack(50.0f);
	}

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
	//	// 몬스터 총알의 공격력을 50으로 설정합니다...
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

	static float Time = 0.f;
	if (!m_bBullet)
		return;
	if (fire_delay < 0)
	{
		m_bBullet = false; // 한번만 불렛 생성(티스트)
		fire_delay = fire_rate;
	}
	if (Time > 0.001f) {
		fire_delay--;
		Time = 0.f;
	}
	Time += fDeltaTime;
	//if (m_state != MONSTER_STATE::DESTORY) {
	//	switch (mPattern) // 업데이트시 정해진 패턴에 맞게 위치를 업데이트
	//	{
	//	case Pattern::SIN:
	//	{
	//		if (CObject::GetPos().y < 700 && CObject::GetPos().y > 0) {
	//			if (m_state == MONSTER_STATE::DONDESTORY)
	//				m_state = MONSTER_STATE::NOMAL;
	//			if (update_count < 0.0f) {
	//				POSITION _vector = CObject::GetVector();
	//				POSITION n_vector = { _vector.y, -_vector.x };			// 몬스터 기준 직교 벡터 
	//				if (bias == 0)
	//					n_vector = n_vector * (-1);
	//				float det = sqrt(n_vector.x * n_vector.x + n_vector.y * n_vector.y);	// 직교벡터의 크기를 구한다...
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
	//				//	printf("현재 위치 : (%f, %f) ---- 방향 : (%f, %f) ---- ceta = %f ----- t_speed = %d\n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, ceta, t_count);

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
	//				//	printf("현재 위치 : (%f, %f) ---- 방향 : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

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
	//				//	printf("현재 위치 : (%f, %f) ---- 방향 : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

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

	//				//	printf("현재 위치 : (%f, %f) ---- 방향 : (%f, %f) ---- count = %d \n", CObject::GetPos().x, CObject::GetPos().y, CObject::GetVector().x, CObject::GetVector().y, count);

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
