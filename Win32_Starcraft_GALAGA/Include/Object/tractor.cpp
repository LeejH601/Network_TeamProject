#include "tractor.h"
#include "BulletList.h"
#include "../Sound/SoundManager.h"

CTractor::CTractor()
{
}

CTractor::CTractor(const CTractor& player)
{
}

CTractor::~CTractor()
{
	m_bulletList->EraseAll();
	delete m_bulletList;
	CMonster::~CMonster();
}

bool CTractor::Init(POSITION LTpos, const Pattern& pattern, const Monster_type& type, POSITION Vector, int StageNum)
{
	CMonster::Init(LTpos, pattern, Monster_type::Vessel, Vector, StageNum);


	if (m_Explode_img == NULL)
	{
		m_Explode_img.Load(TEXT("../Bin/Scene_Back_img/Explode(2).png"));
		m_Explode_img_LT = { 0,0 };
		m_Explode_img_Size = { 256,200 };


	}
	


	m_bulletList = new CBulletList;
	m_bulletList->Init();
	return true;
}

void CTractor::Input(float fDeltaTime)
{
}

void CTractor::Update(float fDeltaTime)
{
	CMonster::Update(fDeltaTime);
	if (CMonster::GetState() == MONSTER_STATE::WAIT) {
		float currenttime = clock();
		if (LastFireTime == NULL || currenttime - LastFireTime > 200) {
			CreateBullet();
			LastFireTime = currenttime;
		}
		currenttime = clock();
		if (LastUpdateTime == NULL || currenttime - LastUpdateTime > 1) {
			m_bulletList->Update(fDeltaTime, DetBulletSize);
			LastUpdateTime = currenttime;
		}
	}
}

void CTractor::LateUpdate(float fDeltaTime)
{
}

bool CTractor::Collision(float fDeltaTime, CBulletList* player_BulletList)
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

	//if (CMonster::Collision(fDeltaTime, player_BulletList))
	//{
	//	m_state = MONSTER_STATE::DESTORY;
	//	return true;
	//}

	//return true;



}

void CTractor::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	if (m_bDie == true)
	{
		RenderExplode(mainhDC, hdc, fDeltaTime);
	}
	else
	{
		CObject::Render(mainhDC, hdc, fDeltaTime);
		m_bulletList->RenderAll(mainhDC, hdc, fDeltaTime);
	}
	
}

void CTractor::CreateBullet()
{
	POSITION b_vector = { 0,1 };
	m_bulletList->PushBack(CObject::GetPos() + CObject::GetSize() / 2, { 10,5 }, b_vector, 150.0f);
}



void CTractor::RenderExplode(HDC mainhDC, HDC hdc, float fDeltaTime)
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

void CTractor::PlayExplodeSound()
{
	if (m_bDie == true && m_PlayExplodeSound == false)
	{
		CSoundManager::GetInst()->playSound_Effect_Explode();
		m_PlayExplodeSound = true;

	}
}

