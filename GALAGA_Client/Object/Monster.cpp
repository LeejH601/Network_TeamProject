#include	"Monster.h"
#include	"BulletList.h"

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


bool CMonster::Init(POSITION LTpos, const Pattern& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum)
{

	if (m_Explode_img == NULL)
	{
		m_Explode_img.Load(L"./Image/Scene_Back_img/Explode(2).png");
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

	return true;
}

void CMonster::Input(float fDeltaTime)
{
}

void CMonster::Update(float fDeltaTime)
{
	if (m_bDie == true)
		return;

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
	//	if (fire_delay < 0)
	//		fire_delay = fire_rate;
	//	fire_delay--;
	//}
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
	if (m_Explode_img_Count == 300)
		m_state = MONSTER_STATE::DESTORY;

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

