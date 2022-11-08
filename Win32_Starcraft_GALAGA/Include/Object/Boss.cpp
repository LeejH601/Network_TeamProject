#include "Boss.h"
#include "Object.h"
#include "BulletList.h"
#include "Player.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundManager.h"

Boss::Boss()
{
}

Boss::Boss(const Boss& player)
{
}

Boss::~Boss()
{
    m_bulletList->EraseAll();
    delete[] m_bulletList;
}

bool Boss::Init(POSITION LTpos, const Monster_type& type, POSITION Vector, int stageNum )
{
    m_bulletList = new CBulletList;
    m_bulletList->Init();
    CMonster::fire_rate = 2000;
    fire_delay = fire_rate;

    if (m_Explode_img == NULL)
    {
        m_Explode_img.Load(TEXT("../Bin/Scene_Back_img/Explode(2).png"));
        m_Explode_img_LT = { 0,0 };
        m_Explode_img_Size = { 256,200 };

    }
    
    
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


    t_speed = 300.0f;
    switch (type)
    {
    case Monster_type::BOSS_ONE:
        CObject::Init(L"../Bin/Terran_img/Battle Cruiser.png", LTpos, Vector, { 100,120 }, 20000.0f * AttackRate, { 74,75 }, { 1, 57 },PLAYER_TYPE::PT_MONSTER);
        break;
    case Monster_type::BOSS_TWO:
        CObject::Init(L"../Bin/Protoss_img/mothership.png", LTpos, Vector, { 100,100 }, 40000.0f* AttackRate, { 67 , 62 }, { 23 ,18 }, PLAYER_TYPE::PT_MONSTER);
        break;
    case Monster_type::BOSS_THREE:
        CObject::Init(L"../Bin/Zerg_img/Guardian.png", LTpos, Vector, { 120,100 }, 65000.0f, { 70  , 40 }, { 650  ,85 },PLAYER_TYPE::PT_MONSTER);
        break;
    default:
        break;
    }
    return true;
}

void Boss::Input(float fDeltaTime)
{

}
void Boss::Update(float fDeltaTime)
{
    POSITION temp_vector = CObject::GetPos();
    float fMovedIstance = 0.00166666f;
    if (temp_vector.y < 50) {
        temp_vector = temp_vector + POSITION{ 0, 1 }*fMovedIstance * t_speed;
        if (temp_vector.y >= 50) {
            CObject::SetVector({ 1,0 });
            if (m_state == MONSTER_STATE::DONDESTORY)
                m_state = MONSTER_STATE::NOMAL;
            t_speed = 100.f;
        }
        CObject::SetPos(temp_vector);
    }
    else {
        POSITION move_vector = CObject::GetVector();
        if (temp_vector.x < 100 || temp_vector.x > 470) {
            move_vector = move_vector * (-1);
            CObject::SetVector(move_vector);
        }
        temp_vector = temp_vector + move_vector * fMovedIstance * t_speed;
        CObject::SetPos(temp_vector);
    }
    if (m_state == MONSTER_STATE::NOMAL) {
        if (fire_delay <= 0) {
            if (pattern_count <= 0) {
                b_pattern = (Pattern)(rand() % 6);
                //b_pattern = Pattern::SIN5;
                switch (b_pattern)
                {
                case Pattern::SIN:
                    pattern_count = 1;
                    break;
                case Pattern::SIN2:
                    pattern_count = 3;
                    fire_rate = 100;
                    break;
                case Pattern::SIN3:
                    pattern_count = 360 / 5;
                    fire_rate = 20;
                    break;
                case Pattern::SIN4:
                    pattern_count = 1440 / 4;
                    fire_rate = 1;
                    break;
                case Pattern::SIN5:
                    accum_ceta = 10;
                    pattern_count = 180 / 4;
                    fire_rate = 100;
                    break;
                case Pattern::SIN6:
                    pattern_count = 1080 / 10;
                    fire_rate = 20;
                    is_reverseCeta = (rand() % 2 == 0) ? true : false;
                    break;
                default:
                    break;
                }
            }
            CreateBullet(b_pattern);
            fire_delay = fire_rate;
        }
        else
            fire_delay--;
    }
    m_bulletList->Update(fDeltaTime);
}
void Boss::LateUpdate(float fDeltaTime)
{

}

bool Boss::Collision(float fDeltaTime, CBulletList* player_BulletList)
{

    int  CollisionCheckNum = player_BulletList->Collision(fDeltaTime, CObject::m_tLTPos, CObject::m_tSize);
    CObject::m_fHP -= (CollisionCheckNum * player_BulletList->GetAttack());

    if (m_bDie == false)
    {
        if (CObject::m_fHP <= 0)
        {
            m_bDie = true;
        }
    }

    return m_bDie;
}

void Boss::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
    if (m_bDie == true)
    {
        RenderExplode(mainhDC, hdc, fDeltaTime);
    }
    else
    {
        CObject::Render(mainhDC, hdc, fDeltaTime);
        //printf("pos = (%f, %f)\n", CObject::GetPos().x, CObject::GetPos().y);
        m_bulletList->RenderAll(mainhDC, hdc, fDeltaTime);

    }

}
void Boss::CreateBullet(Pattern _pattern)
{
    if (m_state != MONSTER_STATE::DONDESTORY && m_state != MONSTER_STATE::DESTORY) {
        switch (_pattern)
        {
        case Pattern::SIN:
        {
            b_vector = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
            CPlayer* player = CSceneManager::GetInst()->GetPlayer();
            b_vector = (player->GetPos() + (player->GetSize() / 3)) - CObject::GetPos();
            b_vector = b_vector / (sqrt(b_vector.x * b_vector.x + b_vector.y * b_vector.y));
            //printf("b_vector = (%f, %f)\n", b_vector.x, b_vector.y);
            m_bulletList->PushBack(CObject::GetPos(), { 15,15 }, b_vector, float(rand() % 200) + B_speed);
        }
        break;
        case Pattern::SIN2:
        {
            POSITION m_pos = CObject::GetPos() + POSITION(CObject::GetSize().x / 2, CObject::GetSize().y);
            b_vector = POSITION{ 0,1 };
            float bullet_ceta;
            for (bullet_ceta = 0; bullet_ceta < 360; bullet_ceta = bullet_ceta + 10) {
                POSITION new_vector = { b_vector.x * cos(bullet_ceta * 3.141592f / 180) - b_vector.y * sin(bullet_ceta * 3.141592f / 180),b_vector.x * sin(bullet_ceta * 3.141592f / 180) + b_vector.y * cos(bullet_ceta * 3.141592f / 180) };
                m_bulletList->PushBack(m_pos, { 15,15 }, new_vector, B_speed);
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
            m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
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
            m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
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

                printf("%d", is_reverseCeta);
            }
            //m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
            accum_ceta = (is_reverseCeta) ? accum_ceta + bullet_ceta : accum_ceta - bullet_ceta;
            printf("accum_ceta : %f \n", accum_ceta);
            m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
            m_bulletList->PushBack(m_pos, { 15,15 }, { -b_vector.x,b_vector.y }, B_speed);
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
            m_bulletList->PushBack(m_pos, { 15,15 }, b_vector, B_speed);
        }
        break;
        default:
            break;
        }
        pattern_count--;
        if (pattern_count == 0) {
            fire_rate = 500;
            accum_ceta = 0;
        }
    }
}



void Boss::RenderExplode(HDC mainhDC, HDC hdc, float fDeltaTime)
{

    m_Explode_img_Count += 1;

    m_Explode_img.Draw(hdc, CObject::m_tLTPos.x - (CObject::m_tSize.x / 2), CObject::m_tLTPos.y - (CObject::m_tSize.y / 2),
        CObject::m_tSize.x + (CObject::m_tSize.x / 2), CObject::m_tSize.y + (CObject::m_tSize.y / 2),
        m_Explode_img_LT.x, m_Explode_img_LT.y, m_Explode_img_Size.x, m_Explode_img_Size.y);

    if (m_Explode_img_Count % 100 == 0)
    {
        m_Explode_img_LT.x = m_Explode_img_LT.x + m_Explode_img_Size.x;

    }
    if (m_Explode_img_Count % (100 * 4) == 0)
    {
        m_Explode_img_LT.x = 5;
        m_Explode_img_LT.y = m_Explode_img_LT.y + m_Explode_img_Size.y;
    }

    // 출력이미지를 전부 출력했을 때 몬스터를 삭제합니다... 
    if (m_Explode_img_Count == 1000)
        m_state = MONSTER_STATE::DESTORY;

}

void Boss::PlayExplodeSound()
{
    if (m_bDie == true && m_PlayExplodeSound == false)
    {
        CSoundManager::GetInst()->playSound_Effect_Explode();
        m_PlayExplodeSound = true;

    }
}
