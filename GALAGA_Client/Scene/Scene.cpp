#include "../Include/Game.h"
#include "Scene.h"

// 주석 - 클래스가 존재하지 않을때
CScene::CScene() : m_bEnable(false), m_bSlide(false)
{
}

CScene::~CScene()
{
	//if (m_MonsterList != nullptr)
	//	(*m_MonsterList).clear();

	//Monster_BulletList->EraseAll();
	//delete Monster_BulletList;

	//m_ItemList->EraseAll();
	//delete m_ItemList;

	//if (m_boss)
	//	delete m_boss;
	//m_boss = nullptr;

	//if (m_Tractor)
	//	delete m_Tractor;
	//m_Tractor = nullptr;




}

void CScene::imgLT_Move(float fDeltaTime)
{
	//float fMovedistY = fDeltaTime * 200 * 1.8f;

	//if (m_imgLT.y <= 0)
	//{
	//	m_imgLT.y = 0;
	//	m_bSlide = true;

	//}



	//if (m_bSlide == true)
	//{

	//	// proto Img
	//	m_imgRenderLT.y += fMovedistY;
	//	m_imgRenderSize.y -= fMovedistY;

	//	m_imgLT.y = 0;
	//	m_imgSize.y -= fMovedistY;


	//	// Second Img
	//	m_imgRenderLT2.y = 0;
	//	m_imgRenderSize2.y = (750 - m_imgRenderSize.y) + 1;

	//	m_imgLT2.y -= fMovedistY;
	//	m_imgSize2.y += fMovedistY;

	//	if (m_imgRenderSize.y <= 1)
	//	{
	//		m_bSlide = false;

	//		// proto init
	//		m_imgLT.y = 4000 - 750;
	//		m_imgSize.y = 750;

	//		m_imgRenderLT.y = 0;
	//		m_imgRenderSize.y = 750;


	//		//second init
	//		m_imgRenderSize2.y = 1;
	//		m_imgLT2.y = 4000;
	//		m_imgSize2.y = 1;



	//	}
	//}
	//else
	//{
	//	m_imgLT.y -= fMovedistY;

	//}


}

void CScene::imgLT_Move_Auto(float fDeltaTime)
{

//	float fMovedistY = fDeltaTime * 200 * 1.7;
//
//	if (m_imgLT.y <= 0)
//	{
//		m_imgLT.y = 0;
//		m_bSlide = true;
//
//	}
//
//
//
//	if (m_bSlide == true)
//	{
//
//		// proto Img
//		m_imgRenderLT.y += fMovedistY;
//		m_imgRenderSize.y -= fMovedistY;
//
//		m_imgLT.y = 0;
//		m_imgSize.y -= fMovedistY;
//
//
//		// Second Img
//		m_imgRenderLT2.y = 0;
//		m_imgRenderSize2.y = (750 - m_imgRenderSize.y) + 1;
//
//		m_imgLT2.y -= fMovedistY;
//		m_imgSize2.y += fMovedistY;
//
//		if (m_imgRenderSize.y <= 1)
//		{
//			m_bSlide = false;
//
//			// proto init
//			m_imgLT.y = 4000 - 750;
//			m_imgSize.y = 750;
//
//			m_imgRenderLT.y = 0;
//			m_imgRenderSize.y = 750;
//
//
//			//second init
//			m_imgRenderSize2.y = 1;
//			m_imgLT2.y = 4000;
//			m_imgSize2.y = 1;
//
//
//
//		}
//	}
//	else
//	{
//		m_imgLT.y -= fMovedistY;
//
//	}
//
}

bool CScene::Init(const WCHAR* imgBackText, CPlayer* player, long long MaxDistance, bool enable, int stageNum)
{
	//m_StageNum = stageNum;

	//if (player != nullptr)
	//{
	//	m_ItemList = new CItemList;
	//	m_ItemList->Init();

	//}


	//auto rst = m_BackImage.Load(imgBackText);

	//// Load Fail -> 무한루프 
	//if (S_OK != rst) {
	//	while (true);
	//}

	////if(m_Player)
	////m_Player = new Cm_Player(*m_Player);
	//m_Player = player;

	//m_MaxDistance = MaxDistance;
	//m_bEnable = enable;
	//m_bEndScene = false;


	//m_imgLT.x = 0;
	//m_imgLT.y = 0;
	//m_imgSize.x = 600;
	//m_imgSize.y = 750;

	//m_imgRenderLT.x = 0;
	//m_imgRenderLT.y = 0;
	//m_imgRenderSize.x = 600;
	//m_imgRenderSize.y = 750;

	//m_imgLT2.x = 0;
	//m_imgLT2.y = 4000;
	//m_imgSize2.x = 600;
	//m_imgSize2.y = 1;

	//m_imgRenderLT2.x = 0;
	//m_imgRenderLT2.y = 0;
	//m_imgRenderSize2.x = 600;
	//m_imgRenderSize2.y = 1;


	//// 사운드를 재생합니다. 
	////PlaySound(TEXT("./Sound/Terran_Theme1.mp3"), NULL, SND_ASYNC | SND_LOOP);

	//if (player != nullptr)
	//{
	//	m_MonsterList = CSceneManager::GetInst()->GetMonsterList();
	//	Monster_BulletList = new CBulletList;
	//	Monster_BulletList->Init();

	//}



	return true;
}

void CScene::AddObject(CMonster* pMonster)
{
}

void CScene::Input(float fDeltaTime, CScene* NextScene)
{
	/*if (m_Player)
		m_Player->Input(fDeltaTime, this, NextScene);*/

}

int CScene::Update(float fDeltaTime)
{
	//// 아이템이 플레이어의 이동거리에 따라서 생성됩니다... ( 랜덤한 아이템 생성 )
	//static int iCOunt = 0;
	//iCOunt += 1;

	//if (iCOunt % 5000 == 0)
	//{
	//	if (m_ItemList)
	//	{

	//		if (m_Player)
	//			m_ItemList->PushBack(ITEM_TYPE::IT_RANDOM);

	//	}
	//	iCOunt = 0;

	//}



	//if (m_Player)
	//{
	//	imgLT_Move_Auto(fDeltaTime);//배경화면이 자동으로 이동합니다...

	//	if (m_Player->GetHitTractorBeam() == true && m_Tractor)
	//	{
	//		POSITION TractorPos = { m_Tractor->GetPos() + m_Tractor->GetSize() / 2 };
	//		POSITION new_Pvector = { TractorPos - (m_Player->GetPos() + m_Player->GetSize() / 2) };
	//		new_Pvector = new_Pvector / sqrt(new_Pvector.x * new_Pvector.x + new_Pvector.y * new_Pvector.y);
	//		m_Player->SetVector(new_Pvector);

	//	}

	//	m_Player->Update(fDeltaTime);
	//	if (I_MspawnCount <= 0) {
	//		Monster_type m_type = (Monster_type)((rand() % 2 + 1) * 10000 + (rand() % 4 + 1));
	//		if ((int)m_Player->GetMyType() <= (int)m_type / 10000)
	//			m_type = (Monster_type)((int)m_type + 10000);

	//		Pattern pattern = (Pattern)(rand() % (int)Pattern::NONE);
	//		pattern = Pattern::SIN;
	//		if (pattern == Pattern::SIN5) {
	//			for (int i = 0; i < 5; i++) {
	//				CMonster* t_mon = new CMonster;
	//				t_mon->Init(POSITION(100, -100 - i * 40), pattern, m_type, POSITION(0, 1), m_StageNum);
	//				m_MonsterList->push_back(t_mon);
	//				t_mon = new CMonster;
	//				t_mon->Init(POSITION(500, -100 - i * 40), pattern, m_type, POSITION(0, 1), m_StageNum);
	//				m_MonsterList->push_back(t_mon);
	//			}
	//		}
	//		else if (pattern == Pattern::SIN6) {
	//			float yPos = float(rand() % 100 + 100);
	//			if (rand() % 2 == 0) {
	//				for (int i = 0; i < 5; i++) {
	//					CMonster* t_mon = new CMonster;
	//					t_mon->Init(POSITION(-100 - i * 40, yPos), pattern, m_type, POSITION(1, 0), m_StageNum);
	//					m_MonsterList->push_back(t_mon);
	//				}
	//			}
	//			else {
	//				for (int i = 0; i < 5; i++) {
	//					CMonster* t_mon = new CMonster;
	//					t_mon->Init(POSITION(700 + i * 40, yPos), pattern, m_type, POSITION(-1, 0), m_StageNum);
	//					m_MonsterList->push_back(t_mon);
	//				}
	//			}
	//		}
	//		else if (pattern == Pattern::SIN4) {
	//			float xPos = float(rand() % 500 + 50);
	//			for (int i = 0; i < 5; i++) {
	//				CMonster* t_mon = new CMonster;
	//				t_mon->Init(POSITION(xPos, -100 - i * 40), pattern, m_type, POSITION(0, 1), m_StageNum);
	//				m_MonsterList->push_back(t_mon);
	//			}

	//		}
	//		else {
	//			if (rand() % 2 == 0) {
	//				for (int i = 0; i < 5; i++) {
	//					CMonster* t_mon = new CMonster;
	//					t_mon->Init(POSITION(100, -100 - i * 40), pattern, m_type, POSITION(0, 1), m_StageNum);
	//					m_MonsterList->push_back(t_mon);
	//				}
	//			}
	//			else {
	//				for (int i = 0; i < 5; i++) {
	//					CMonster* t_mon = new CMonster;
	//					t_mon->Init(POSITION(500, -100 - i * 40), pattern, m_type, POSITION(0, 1), m_StageNum);
	//					m_MonsterList->push_back(t_mon);
	//				}
	//			}
	//		}
	//		I_MspawnCount = I_MspawnDelay + (rand() % 3000 - 2000);
	//	}
	//	else
	//		I_MspawnCount--;

	//	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
	//		(*it)->Update(fDeltaTime);
	//		if ((*it)->GetFireDelay() <= 0)
	//			(*it)->CreateBullet(&Monster_BulletList);
	//		if ((*it)->GetState() == MONSTER_STATE::DESTORY) {
	//			/*list<CMonster*>::iterator temp = it;
	//			it--;*/
	//			//m_MonsterList->remove(temp._Unwrapped());
	//			(*it)->~CMonster();
	//			it = m_MonsterList->erase(it);
	//			if (it != m_MonsterList->begin())
	//				it--;
	//			else if (it == m_MonsterList->end()) {
	//				break;
	//			}
	//		}
	//	}
	//	Monster_BulletList->Update(fDeltaTime);

	//	if (m_boss == nullptr && m_Distance >= m_MaxDistance) {
	//		m_boss = new Boss;

	//		if (m_StageNum == 1)
	//		{
	//			m_boss->Init(POSITION{ 300,-100 }, Monster_type::BOSS_ONE, { 0,1 }, m_StageNum);
	//			CSoundManager::GetInst()->PlaySound_Bossbgm(m_StageNum);

	//		}
	//		else if (m_StageNum == 2)
	//		{
	//			m_boss->Init(POSITION{ 300,-100 }, Monster_type::BOSS_TWO, { 0,1 }, m_StageNum);
	//			CSoundManager::GetInst()->PlaySound_Bossbgm(m_StageNum);

	//		}
	//		else if (m_StageNum == 3)
	//		{
	//			m_boss->Init(POSITION{ 300,-100 }, Monster_type::BOSS_THREE, { 0,1 }, m_StageNum);
	//			CSoundManager::GetInst()->PlaySound_Bossbgm(m_StageNum);

	//		}

	//	}

	//	if (m_boss != nullptr) {
	//		m_boss->Update(fDeltaTime);
	//	}

	//	if (m_Tractor == nullptr && m_Distance > m_MaxDistance / 2) {
	//		TractorCount_Render += 1;

	//		if (TractorCount_Render == 3000)
	//		{
	//			m_Tractor = new CTractor;
	//			m_Tractor->Init(POSITION{ 300,-100 }, Pattern::SIN7, Monster_type::Vessel, { 0,1 }, m_StageNum);

	//		}

	//	}

	//	if (m_Tractor != nullptr) {
	//		m_Tractor->Update(fDeltaTime);
	//	}


	//}

	//if (m_bEndScene)
	//	return 1;

	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	/*if (m_Player == nullptr)
		return 0;


	if (m_Player)
		m_Player->LateUpdate(fDeltaTime);

	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
		(*it)->PlayExplodeSound();

		if ((*it)->GetState() == MONSTER_STATE::DESTORY) {
			(*it)->~CMonster();
			it = m_MonsterList->erase(it);
			if (it != m_MonsterList->begin())
				it--;
			else if (it == m_MonsterList->end()) {
				break;
			}
		}
	}
	if (m_Tractor)
	{
		if (m_Tractor->GetState() == MONSTER_STATE::DESTORY)
		{

			POSITION TractorPos = m_Tractor->GetPos();
			POSITION TractorSize = m_Tractor->GetSize();


			delete m_Tractor;
			m_Tractor = nullptr;

			m_ItemList->PushBack(ITEM_TYPE::IT_RANDOM, TractorPos, TractorSize, 100.0f);

		}


	}

	if (m_ItemList)
		m_ItemList->Update(fDeltaTime);*/



	return 0;
}


void CScene::Collision(float fDeltaTime)
{
	//if (m_Player == nullptr)
	//	return;


	//if (m_Player)
	//	m_Player->Collision(fDeltaTime, { 0,0 }, { 0,0 });


	//// 몬스터와 플레이어의 총알과 충돌체크 합니다...
	//for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++)
	//{
	//	if ((*it)->GetState() == MONSTER_STATE::DONDESTORY || (*it)->GetIsDie() == true)
	//		continue;
	//	// 몬스터와 플레이어 총알과 충돌체크 합니다... 
	//	(*it)->Collision(fDeltaTime, m_Player->GetmyBulletList());

	//	// 충돌 후 몬스터의 상태가 DESTROY 이면 삭제합니다...
	//	if ((*it)->GetState() == MONSTER_STATE::DESTORY) {
	//		(*it)->~CMonster();
	//		it = m_MonsterList->erase(it);
	//		if (it != m_MonsterList->begin())
	//			it--;
	//		else if (it == m_MonsterList->end()) {
	//			break;
	//		}
	//	}
	//}

	//if (m_Tractor)
	//	m_Tractor->Collision(fDeltaTime, m_Player->GetmyBulletList());


	//if (m_boss)
	//{
	//	// 보스가 죽었다면 
	//	m_boss->Collision(fDeltaTime, m_Player->GetmyBulletList());
	//	//	m_bEndScene = true;
	//	if (m_boss->GetState() == MONSTER_STATE::DESTORY)
	//		m_bEndScene = true;

	//}

	//// 플레이어와 몬스터 총알과 충돌체크 합니다...
	//if (m_Player)
	//{
	//	m_Player->Collision(fDeltaTime, Monster_BulletList);

	//	// 보스의 총알과 충돌체크 합니다...
	//	if (m_boss)
	//		m_Player->Collision(fDeltaTime, m_boss->GetMyBulletList());

	//	// 트랙터 빔과 충돓체크 합니다... 
	//	if (m_Tractor)
	//	{

	//		bool bCollisionCheck = false;
	//		if (m_Player)
	//		{
	//			if (m_Player->GetINVINVIBILITY() == false)
	//			{
	//				//m_Tractor->Collision(fDeltaTime, m_Player->GetmyBulletList());
	//				bCollisionCheck = m_Player->Collision(fDeltaTime, m_Tractor->GetMyBulletList(), 0);
	//				if (m_Tractor->GetState() == MONSTER_STATE::DESTORY)
	//					delete m_Tractor;

	//			}
	//			//bCollisionCheck = m_Player->Collision(fDeltaTime, m_Tractor->GetMyBulletList(), 0);
	//		}

	//		if (bCollisionCheck == true)
	//			m_Player->SetHitTractorBeam(true);
	//		//else if (bCollisionCheck == false)
	//		//	m_Player->SetHitTractorBeam(false);

	//	}
	//	else
	//		m_Player->SetHitTractorBeam(false);



	//	// 아이템과의 충돌 체크 

	//	if (m_ItemList)
	//		m_ItemList->Collision(fDeltaTime, m_Player->GetPos(), m_Player->GetSize(), m_Player);
	//}








}

void CScene::Render(HDC mainhDC, HDC hDC, float fDeltaTime)
{


	//// 배경화면을 출력합니다... <  화면이 이어집니다... >
	//if (m_bSlide == true)
	//{

	//	// Back Image Render 
	//	m_BackImage.Draw(hDC, m_imgRenderLT.x, m_imgRenderLT.y, m_imgRenderSize.x, m_imgRenderSize.y,
	//		m_imgLT.x, m_imgLT.y, m_imgSize.x, m_imgSize.y);

	//	// Back Image Render 
	//	m_BackImage.Draw(hDC, m_imgRenderLT2.x, m_imgRenderLT2.y, m_imgRenderSize2.x, m_imgRenderSize2.y,
	//		m_imgLT2.x, m_imgLT2.y, m_imgSize2.x, m_imgSize2.y);

	//}

	//else if (m_bSlide == false)
	//{

	//	// Back Image Render 
	//	m_BackImage.Draw(hDC, m_imgRenderLT.x, m_imgRenderLT.y, m_imgRenderSize.x, m_imgRenderSize.y,
	//		m_imgLT.x, m_imgLT.y, m_imgSize.x, m_imgSize.y);



	//}


	//// 플레이어를 출력합니다...
	//if (m_Player)
	//{
	//	m_Player->Render(mainhDC, hDC, fDeltaTime);
	//	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
	//		(*it)->Render(mainhDC, hDC, fDeltaTime);
	//	}
	//	// 몬스터 총알을 출력합니다...
	//	Monster_BulletList->RenderAll(mainhDC, hDC, fDeltaTime);

	//	// 보스를 출력합니다...
	//	if (m_boss != nullptr) {
	//		m_boss->Render(mainhDC, hDC, fDeltaTime);
	//	}
	//	// 트랙터 출력
	//	if (m_Tractor != nullptr) {
	//		m_Tractor->Render(mainhDC, hDC, fDeltaTime);
	//	}

	//}


	//if (m_ItemList)
	//	m_ItemList->RenderAll(mainhDC, hDC, fDeltaTime);



	//// MemDc 에 있는 화면을 main HDC 에 출력합니다... < 최종 출력 >
	//BitBlt(mainhDC, 0, 0, 600, 750, hDC, 0, 0, SRCCOPY);

}

void CScene::UpdateMaxDistance(double distance, CScene* NextScene)
{
	m_Distance += distance;
	//if (m_Distance >= m_MaxDistance)
	//{
	//	m_bEndScene = true;

	//	//// 현재 스테이지 출력을 중지합니다..
	//	//this->m_bEnable = false;
	//	//// 다음 스테이지를 출력하게 합니다...
	//	//NextScene->SetEnable(true);
	//	//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 2);

	//}


}




