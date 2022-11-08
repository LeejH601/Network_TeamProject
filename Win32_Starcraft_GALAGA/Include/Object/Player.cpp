#include	"Player.h"
#include	"../Scene/Scene.h"
#include	"../Scene/SceneManager.h"
#include	"Bullet.h"
#include	"BulletList.h"
#include	"../Sound/SoundManager.h"
#include "ItemList.h"
#include "Item.h"




CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& player) :
	CObject(player)
{
	m_fSpeed = player.m_fSpeed;

}

CPlayer::~CPlayer()
{
	CObject::~CObject();

	if (m_myBulletList)
		m_myBulletList->EraseAll();

}



void CPlayer::AddAttack()
{
	m_myBulletList->AddAttack();

}

bool CPlayer::Init()
{
	int i = 0;

	if(m_Invincibility_img == NULL)
 	m_Invincibility_img.Load(TEXT("../Bin/Item_img/invincibility (2).png"));
	//m_Invincibility_img.SetTransparentColor(RGB(255, 255, 255));

	//750 - (PlayerSize.y * 2)
	

	if (m_MyType == OBJECT_TYPE::OT_TERRAN)
	{
		POSITION PlayerVector = { 0 , -100 };
		_SIZE PlayerSize = { 60,60 };
		POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
		POSITION PlayerimgSize = { 46,41 };
		POSITION PlayerimgLT = { 15 * 46, 0 };

		m_fHP_prototype = 1000.0f;

		CObject::Init(L"../Bin/Terran_img/Wraith.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
		m_fSpeed = 300.0f;
	}
	else if (m_MyType == OBJECT_TYPE::OT_PROTOSS)
	{
		POSITION PlayerVector = { 0 , -100 };
		_SIZE PlayerSize = { 60,60 };
		POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
		POSITION PlayerimgSize = { 31,35 };
		POSITION PlayerimgLT = { 285, 11 };

		m_fHP_prototype = 1000.0f;

		CObject::Init(L"../Bin/Protoss_img/scout.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
		m_fSpeed = 300.0f;
	}
	else if (m_MyType == OBJECT_TYPE::OT_ZERG)
	{

		POSITION PlayerVector = { 0 , -100 };
		_SIZE PlayerSize = { 60,60 };
		POSITION PlayerLT = { 600 / 2 - PlayerSize.x , 400 };
		POSITION PlayerimgSize = { 52,61 };
		POSITION PlayerimgLT = { 10, 101 };

		m_fHP_prototype = 1000.0f;

		CObject::Init(L"../Bin/Zerg_img/Devourer.png", PlayerLT, PlayerVector, PlayerSize, m_fHP_prototype, PlayerimgSize, PlayerimgLT, PLAYER_TYPE::PT_PLAYER);
		m_fSpeed = 300.0f;
	}

	m_myBulletList = new CBulletList;
	m_myBulletList->Init();

	m_BulletShotCount = 0;



	return true;
}

void CPlayer::Input(float fDeltaTime, CScene* CurScene, CScene* NextScene)
{
	

	if (m_bHit_TractorBeam == false) {
		if (GetAsyncKeyState('A') & 0x8000)
		{
			CObject::m_tLTPos.x -= fDeltaTime * m_fSpeed;


			if (CObject::m_tLTPos.x < 0)
				CObject::m_tLTPos.x = 0.0f;


		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			CObject::m_tLTPos.x += fDeltaTime * m_fSpeed;


			if (CObject::m_tLTPos.x > 600 - CObject::m_tSize.x)
				CObject::m_tLTPos.x = 600 - CObject::m_tSize.x;

		}
		if (GetAsyncKeyState('W') & 0x8000)
		{
			//CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;

			if (CObject::m_tLTPos.y >= 750 / 2 + 250)
				CObject::m_tLTPos.y -= fDeltaTime * m_fSpeed;
			//if (CObject::m_tLTPos.y < 750 / 2 + 250)
			//	CObject::m_tLTPos.y = 750 / 2 + 250;

			// 위에 키를 누를 때 배경화면이 움직입니다...
			CurScene->imgLT_Move(fDeltaTime);
			CurScene->UpdateMaxDistance(fDeltaTime * m_fSpeed, NextScene);	// 현재 Scene 의 이동거리를 누적합니다... 


		}


		if (GetAsyncKeyState('S') & 0x8000)
		{
			CObject::m_tLTPos.y += fDeltaTime * m_fSpeed;


			if (CObject::m_tLTPos.y > 750 - CObject::m_tSize.y)
				CObject::m_tLTPos.y = 750 - CObject::m_tSize.y;

		}
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		/*if (m_BulletShotCount > 0)
			m_BulletShotCount -= 1;
		if (m_BulletShotCount <= 0)
		{

			if (m_myBulletList != nullptr)

				m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
			m_BulletShotCount = 100;

			CSoundManager::GetInst()->playSound_Effect();

		}*/
		float currentTime = clock();
		if (m_LastFireTime == NULL || currentTime - m_LastFireTime >= 100) {
			if (m_myBulletList != nullptr)
			{

				if(m_BulletNum == 1)
				m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
				else if (m_BulletNum == 2)
				{
					m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x - 13, m_tLTPos.y }, m_tSize, 800.0f);

				}
				else if (m_BulletNum == 3)
				{
					m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x - 13, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x + 13, m_tLTPos.y }, m_tSize, 800.0f);

				}
				else if (m_BulletNum == 4)
				{
					m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x - 13, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x + 13, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x + 26, m_tLTPos.y }, m_tSize, 800.0f);

				}
				else if (m_BulletNum == 5)
				{
					m_myBulletList->PushBack(m_tLTPos, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x - 26, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x - 13, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x + 13, m_tLTPos.y }, m_tSize, 800.0f);
					m_myBulletList->PushBack({ m_tLTPos.x + 26, m_tLTPos.y }, m_tSize, 800.0f);

				}
				
			}
			m_LastFireTime = currentTime;
			m_BulletShotCount = 100;

			// 총알 소리
			CSoundManager::GetInst()->playSound_Effect();
		}
	}


	if (GetAsyncKeyState('P') & 0x8000)
	{
		b_NotDie_Test = true;


	}



}

void CPlayer::Update(float fDeltaTime)
{
	if (m_bHit_TractorBeam) {
		float fMovedIstance = 0.0016666f;
		POSITION n_pos = CObject::GetPos() + (CObject::GetVector() * fMovedIstance) * (m_fSpeed / 2); ;
		CObject::SetPos(n_pos);
	}
	else {
		if (CObject::GetPos().y < 750 / 2 + 250) {
			float fMovedIstance = 0.0016666f;
			POSITION n_pos = CObject::GetPos() + (POSITION(0, 1) * fMovedIstance) * (m_fSpeed / 2); ;
			CObject::SetPos(n_pos);
		}
	}
	CObject::Update(fDeltaTime);


	if (m_myBulletList)
		m_myBulletList->Update(fDeltaTime);


}

void CPlayer::LateUpdate(float fDeltaTime)
{
}

bool CPlayer::Collision(float fDeltaTime, POSITION ObjectLT = { 0,0 }, POSITION ObjectSize = { 0,0 })
{

	return false;

}

bool CPlayer::Collision(float fDeltaTime, CBulletList* player_BulletList)
{
	if (m_bINVINVIBILITY == true)
		m_INVINVIBILITY_Count += 1;

	if (m_INVINVIBILITY_Count == 3000)
	{
		m_bINVINVIBILITY = false;
		m_INVINVIBILITY_Count = 0;

	}
	int  CollisionCheckNum = player_BulletList->Collision(fDeltaTime, CObject::m_tLTPos, CObject::m_tSize);
	if (m_bINVINVIBILITY == false || b_NotDie_Test == true)
	CObject::m_fHP -= (CollisionCheckNum * player_BulletList->GetAttack());

	if (m_bDie == false)
	{
		if (CObject::m_fHP <= 0)
		{
			m_bDie = true;
		}
	}


	return true;
}

bool CPlayer::Collision(float fDeltaTime, CItemList* itemList)
{
	
	return true;

}

bool CPlayer::Collision(float fDeltaTime, CBulletList* player_BulletList, int i)
{
	int  CollisionCheckNum = player_BulletList->Collision(fDeltaTime, CObject::m_tLTPos, CObject::m_tSize);
	if (CollisionCheckNum > 0)
		return true;
	else
		return false;


}


void CPlayer::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{
	CObject::Render(mainhDC, hdc, fDeltaTime);
	if (m_bINVINVIBILITY == true)
	{
		m_Invincibility_img.Draw(hdc, CObject::m_tLTPos.x - (m_tSize.x / 3)- 10, 
			CObject::m_tLTPos.y - (m_tSize.y / 3) - 10, CObject::m_tSize.x + (m_tSize.x / 2) + 20,
			CObject::m_tSize.y + (m_tSize.y / 2) + 10, 0, 0, 190, 190);

	}



	if (m_myBulletList)
		m_myBulletList->RenderAll(mainhDC,hdc, fDeltaTime);

}

void CPlayer::RenderBulletList(HDC mainhDC, HDC hdc , float fDeltaTime)
{
	if (m_myBulletList)
		m_myBulletList->RenderAll(mainhDC, hdc, fDeltaTime);

}



