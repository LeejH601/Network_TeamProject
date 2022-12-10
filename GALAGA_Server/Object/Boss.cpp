#include "Boss.h"
#include "Player.h"
#include "..\Scene\SceneManager.h"
#include "..\Locator.h"

CBoss::CBoss()
{
	m_bulletList = new CBulletList;
}

CBoss::~CBoss()
{
	delete m_bulletList;
}

bool CBoss::Init(POSITION LTpos, const OBJECT_TYPE& type, POSITION Vector, int stageNum)
{
	CObject::SetObjType(type);


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
		CObject::Init( LTpos, Vector, { 100,120 },  20000.0f * AttackRate,  PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_BOSS_TWO:
		CObject::Init(LTpos, Vector, { 100,100 }, 40000.0f * AttackRate,  PLAYER_TYPE::PT_MONSTER);
		break;
	case OBJECT_TYPE::OBJ_BOSS_THREE:
		CObject::Init( LTpos, Vector, { 120,100 }, 65000.0f, PLAYER_TYPE::PT_MONSTER);
		break;
	default:
		break;
	}

	SetState(OBJECT_STATE::IDLE);
	fire_delay = fire_rate = 2.0f;

	return true;
}

void CBoss::Update(float fDeltaTime)
{
	CObject::Update(fDeltaTime);

	if (m_bDie == false)
	{
		if (CObject::m_fHP <= 0)
		{
			m_fStateTerm = 0.0f;
			m_bDie = true;
			SetState(OBJECT_STATE::DESTORY);
			return;
		}

		else
		{
			if (GetPos().y < 100)
				SetPos(GetPos() + POSITION(0, 1) * fDeltaTime * 35.0f);
			else {
				if (bMoveRight)
				{
					SetPos(GetPos() + POSITION(1, 0) * fDeltaTime * 35.0f);
					if (GetPos().x > 500)
						bMoveRight = false;
				}
				else
				{
					SetPos(GetPos() + POSITION(-1, 0) * fDeltaTime * 35.0f);
					if (GetPos().x < 100)
						bMoveRight = true;
				}
			}

			if (fire_delay <= 0.f) {
				if (pattern_count <= 0) {
					m_Pattern = (Pattern)(rand() % 6);
					//b_pattern = Pattern::SIN5;
					switch (m_Pattern)
					{
					case Pattern::SIN:
						pattern_count = 1;
						break;
					case Pattern::SIN2:
						pattern_count = 3;
						fire_rate = 0.2f;
						break;
					case Pattern::SIN3:
						pattern_count = 72;
						fire_rate = 0.08f;
						break;
					case Pattern::SIN4:
						pattern_count = 360;
						fire_rate = 0.008f;
						break;
					case Pattern::SIN5:
						accum_ceta = 10;
						pattern_count = 45;
						fire_rate = 0.2f;
						break;
					case Pattern::SIN6:
						pattern_count = 108;
						fire_rate = 0.08f;
						is_reverseCeta = (rand() % 2 == 0) ? true : false;
						break;
					default:
						break;
					}
				}
				CreateBullet(m_Pattern);
				fire_delay = fire_rate;
			}
			else
				fire_delay -= fDeltaTime;
		}
	}
	else
	{
		switch (m_eObjState) {
		case OBJECT_STATE::DESTORY:
			m_fStateTerm += fDeltaTime;
			// 3초 뒤 State가 Erase로 바뀜
			if (m_fStateTerm >= 3.0f)
				SetState(OBJECT_STATE::ERASE);
			break;
		case OBJECT_STATE::ERASE:
			break;
		}
	}
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

void CBoss::CreateBullet(Pattern _pattern)
{
	if (GetObjectState() != OBJECT_STATE::DONDESTORY && GetObjectState() != OBJECT_STATE::DESTORY) {
		//std::cout << "boss bullet" << std::endl;
		switch (_pattern)
		{
		case Pattern::SIN:
		{
			b_vector = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			CPlayer* player = Locator.GetPlayer(rand() % 2);
			b_vector = (player->GetPos() + (player->GetSize() / 3)) - CObject::GetPos();
			b_vector = b_vector / (sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y));
			//printf("b_vector = (%f, %f)\n", b_vector.x, b_vector.y);
			m_bulletList->AddBullet(CObject::GetPos(), { 15,15 }, b_vector, float(rand() % 200) + B_speed);
		}
		break;
		case Pattern::SIN2:
		{
			POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			b_vector = POSITION{ 0,1 };
			float bullet_ceta;
			for (bullet_ceta = 0; bullet_ceta < 360; bullet_ceta = bullet_ceta + 10) {
				POSITION new_vector = { b_vector.x * cos(bullet_ceta * 3.141592f / 180) - b_vector.y * sin(bullet_ceta * 3.141592f / 180),b_vector.x * sin(bullet_ceta * 3.141592f / 180) + b_vector.y * cos(bullet_ceta * 3.141592f / 180) };
				m_bulletList->AddBullet(m_pos, { 15,15 }, new_vector, B_speed);
			}
		}
		break;
		case Pattern::SIN3:
		{
			POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			float bullet_ceta = 5;
			float Det = sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y);
			b_vector = POSITION{ b_vector.x * cos(bullet_ceta) - b_vector.y * sin(bullet_ceta),b_vector.x * sin(bullet_ceta) + b_vector.y * cos(bullet_ceta) };

			//   printf("b_vector : (%f, %f)\n", b_vector.x, b_vector.y);
			m_bulletList->AddBullet(m_pos, { 15,15 }, b_vector, B_speed);
		}
		break;
		case Pattern::SIN4:
		{
			POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			float Det = sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y);
			b_vector = POSITION{ 0,1 };
			b_vector = POSITION{ b_vector.x * cos(accum_ceta) - b_vector.y * sin(accum_ceta),b_vector.x * sin(accum_ceta) + b_vector.y * cos(accum_ceta) };
			//   printf("b_vector : (%f, %f)\n", b_vector.x, b_vector.y);
			float bullet_ceta = 0.75;
			accum_ceta = accum_ceta + bullet_ceta;
			m_bulletList->AddBullet(m_pos, { 15,15 }, b_vector, B_speed);
		}
		break;
		case Pattern::SIN5:
		{
			POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			b_vector = POSITION{ 0 ,1 };
			b_vector = POSITION{ b_vector.x * cos(accum_ceta * 3.141592f / 180) - b_vector.y * sin(accum_ceta * 3.141592f / 180),b_vector.x * sin(accum_ceta * 3.141592f / 180) + b_vector.y * cos(accum_ceta * 3.141592f / 180) };
			//b_vector = POSITION{ b_vector.x * cos(15.0f) - b_vector.y * sin(15.0f),b_vector.x * sin(15.0f) + b_vector.y * cos(15.0f) };
			float bullet_ceta = 4.0f;
			if (accum_ceta > 30 || accum_ceta < -30) {
				is_reverseCeta = !is_reverseCeta;

				//printf("%d", is_reverseCeta);
			}
			//m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
			accum_ceta = (is_reverseCeta) ? accum_ceta + bullet_ceta : accum_ceta - bullet_ceta;
			//printf("accum_ceta : %f \n", accum_ceta);
			m_bulletList->AddBullet(m_pos, { 15,15 }, b_vector, B_speed);
			m_bulletList->AddBullet(m_pos, { 15,15 }, { -b_vector.x,b_vector.y }, B_speed);
		}
		break;
		case Pattern::SIN6:
		{
			POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
			float bullet_ceta = (is_reverseCeta) ? 10 : -10;
			float Det = sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y);
			//b_vector = POSITION{ b_vector.x * cos(bullet_ceta) - b_vector.y * sin(bullet_ceta),b_vector.x * sin(bullet_ceta) + b_vector.y * cos(bullet_ceta) };
			b_vector = POSITION{ b_vector.x * cos(bullet_ceta * 3.141592f / 180) - b_vector.y * sin(bullet_ceta * 3.141592f / 180),b_vector.x * sin(bullet_ceta * 3.141592f / 180) + b_vector.y * cos(bullet_ceta * 3.141592f / 180) };
			//   printf("b_vector : (%f, %f)\n", b_vector.x, b_vector.y);
			m_bulletList->AddBullet(m_pos, { 15,15 }, b_vector, B_speed);
		}
		break;
		default:
			break;
		}
		pattern_count--;
		if (pattern_count == 0) {
			fire_rate = 2.0f;
			accum_ceta = 0;
		}
	}
}
