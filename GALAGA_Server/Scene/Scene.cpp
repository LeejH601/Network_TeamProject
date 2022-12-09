#include "..\Core.h"
#include "../Include/Game.h"
#include "../Object/Player.h"
#include "../Object/Item.h"
#include "../Object/Monster.h"
#include "..\Object\Boss.h"
#include "../Object/BulletList.h"
#include "../Object/Bullet.h"
#include "SceneManager.h"
#include "Scene.h"
//#include "..\Object\Boss.h"

CScene::CScene() : m_bEnable(false), m_bSlide(false)
{
	// Monster, Bullet Ȯ�ο� ���� - �����
	m_MonsterList = CSceneManager::GetInst()->GetMonsterList();
	Monster_BulletList = new CBulletList;


}

CScene::~CScene()
{
	if (m_MonsterList != nullptr)
		(*m_MonsterList).clear();

	Monster_BulletList->EraseAll();
	delete Monster_BulletList;

	for (std::list<CItem*>::iterator p = m_ItemList.begin();
		p != m_ItemList.end(); ++p)
	{
		CObjectManager::GetInst()->RemoveObject((*p)->GetID());
		delete (*p);
	}

	m_ItemList.clear();
	//delete m_ItemList;

	//if (m_boss)
	//	delete m_boss;
	//m_boss = nullptr;

	//if (m_Tractor)
	//	delete m_Tractor;
	//m_Tractor = nullptr;




}

bool CScene::Init(class CPlayer* player1, class CPlayer* player2, long long MaxDistance, bool enable, int stageNum)
{
	m_StageNum = stageNum;

	// Create ItemList
	//if (player != nullptr)
	//{
	//	m_ItemList = new CItemList;
	//	m_ItemList->Init();
	//}

	m_Player1 = player1;
	m_Player2 = player2;

	m_MaxDistance = MaxDistance;
	m_bEnable = enable;
	m_bEndScene = false;

	// Get MonsterList and init Monster Bullet List
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

int CScene::Update(float fDeltaTime)
{
	if (m_Player1)
	{
		m_Player1->Update(fDeltaTime);
	}
	if (m_Player2)
	{
		m_Player2->Update(fDeltaTime);
	}

	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
		(*it)->Update(fDeltaTime);
		if ((*it)->GetFireDelay() <= FLT_EPSILON)
		{
			//(*it)->CreateBullet(Monster_BulletList);
		}
	}

	if (m_boss) {
		//m_boss->Update(fDeltaTime);
		UpdateBulletListWithBoss();
	}

	Monster_BulletList->Update(fDeltaTime);

	static float MspawnTime = 5.0f;
	static MONSTER_PATTERN pattern;
	static bool bIsSpawning = false;
	static float spawn_delay = 0.3f;
	static float spawn_count = 0.0f;
	static int ramain_spawn_mobs = 5;

	if (MspawnTime > 5.0f)
	{
		OBJECT_TYPE m_type = (OBJECT_TYPE)((rand() % 2 + 1) * 10000 + (rand() % 4 + 1));
		//if ((int)m_Player->GetMyType() <= (int)m_type / 10000)
		//	m_type = (Monster_type)((int)m_type + 10000);
		if (!bIsSpawning) {
			pattern = (MONSTER_PATTERN)(rand() % (int)MONSTER_PATTERN::END_ENUM);
			bIsSpawning = true;
		}
		{
			spawn_count -= fDeltaTime;
			if (spawn_count <= 0.0f) {
				CMonster* mob = new CMonster;
				mob->Init(POSITION(0, 0), pattern, m_type, POSITION(0, 1), m_StageNum);
				m_MonsterList->push_back(mob);
				ramain_spawn_mobs--;
				spawn_count = spawn_delay;
				if (ramain_spawn_mobs < 0) {
					bIsSpawning = false;
					spawn_count = 0.0f;
					MspawnTime = 0.0f;
					ramain_spawn_mobs = 5;
				}
			}
			
		}
		//MspawnTime = 0.f;
	}

	MspawnTime += fDeltaTime;
	//MspawnTime += 300.0f * fDeltaTime;

	//Monster Bullet ���� Ȯ�ο�
	//static float Time = 0.f;
	//if (Time > 5.f) {
	//	//for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
	//	//	(*it)->Update(fDeltaTime);
	//		Monster_BulletList->AddBullet(POSITION(50.f, 50.f), _SIZE(20.f, 20.f), 5.f);
	//	//}
	//	Time = 0.f;
	//}
	//Time += fDeltaTime;
	//Monster_BulletList->Update(fDeltaTime);

	//imgLT_Move_Auto(fDeltaTime);//���ȭ���� �ڵ����� �̵��մϴ�...

   /* if (I_MspawnCount <= 0) {*/




		//I_MspawnCount = I_MspawnDelay + (rand() % 3000 - 2000);

	//else
	//	Time2 = 0.f;
	
    //else
    	//I_MspawnCount--;


	//// �������� �÷��̾��� �̵��Ÿ��� ���� �����˴ϴ�... ( ������ ������ ���� )
	//static int iCOunt = 0;
	//iCOunt += 1;
    fItemSpawn -= fDeltaTime;

	if (fItemSpawn < FLT_EPSILON)
	{
		CItem* pItem = new CItem;
		pItem->Init(OBJECT_TYPE::IT_RANDOM, { 25.f + rand() % 525, 30 });
		m_ItemList.push_back(pItem);

		fItemSpawn = 0.5f;
	}

	if (m_StageNum)
	{
		UpdateMaxDistance(fDeltaTime * 300.0f);

		if (m_boss == nullptr && m_Distance >= m_MaxDistance)
		{
			//m_bEndScene = true;
			m_boss = new CBoss;

			if (m_StageNum == 1)
			{
				m_boss->Init(POSITION{ 300,100 }, OBJECT_TYPE::OBJ_BOSS_ONE, { 0,1 }, m_StageNum);
				m_MonsterList->push_back(m_boss);
			}
			else if (m_StageNum == 2)
			{
				m_boss->Init(POSITION{ 300,100 }, OBJECT_TYPE::OBJ_BOSS_TWO, { 0,1 }, m_StageNum);
				m_MonsterList->push_back(m_boss);

			}
			else if (m_StageNum == 3)
			{
				m_boss->Init(POSITION{ 300,100 }, OBJECT_TYPE::OBJ_BOSS_THREE, { 0,1 }, m_StageNum);
				m_MonsterList->push_back(m_boss);
			}
		}
	}


	//// Need To Delete
	//else
	//{
	//	UpdateMaxDistance(fDeltaTime * 300.0f);
	//	if (m_Distance >= m_MaxDistance && m_boss == nullptr && m_StageNum > 0)
	//	{
	//		//m_bEndScene = true;
	//		m_boss = new CBoss;

	//		if (m_StageNum == 1)
	//		{
	//			m_boss->Init(POSITION{ 250,-100 }, OBJECT_TYPE::OBJ_BOSS_ONE, { 0,1 }, m_StageNum);

	//		}
	//		else if (m_StageNum == 2)
	//		{
	//			m_boss->Init(POSITION{ 250,-100 }, OBJECT_TYPE::OBJ_BOSS_TWO, { 0,1 }, m_StageNum);

	//		}
	//		else if (m_StageNum == 3)
	//		{
	//			m_boss->Init(POSITION{ 250,-100 }, OBJECT_TYPE::OBJ_BOSS_THREE, { 0,1 }, m_StageNum);
	//		}
	//	}
	//}

	if (!m_ItemList.empty())
	{
		for (std::list<CItem*>::iterator lBegin = m_ItemList.begin();
			lBegin != m_ItemList.end(); ++lBegin)
		{
			if ((*lBegin))
				(*lBegin)->Update(fDeltaTime);
		}
	}

	if (m_bEndScene)
		return 1;
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
	if (m_Player1)
		(m_Player1->GetmyBulletList())->LateUpdate(fDeltaTime);
	if (m_Player2)
		(m_Player2->GetmyBulletList())->LateUpdate(fDeltaTime);

	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
		if ((*it)->GetObjectState() == OBJECT_STATE::ERASE) {
			CMonster* pMonster = *it;
			(*it)->~CMonster();
			CObjectManager::GetInst()->RemoveObject((*it)->GetID());
			it = m_MonsterList->erase(it);
			SAFE_DELETE(pMonster);
			if (it != m_MonsterList->begin())
				it--;
			else if (it == m_MonsterList->end()) {
				break;
			}
		}
	}

	for (list<CItem*>::iterator it = m_ItemList.begin(); it != m_ItemList.end(); it++) {
		if (!(*it)->GetEnbale() && (*it)->GetObjectState() == OBJECT_STATE::ERASE) {
			CItem* pItem = *it;
			CObjectManager::GetInst()->RemoveObject((*it)->GetID());
			it = m_ItemList.erase(it);
			SAFE_DELETE(pItem);
			if (it != m_ItemList.begin())
				it--;
			else if (it == m_ItemList.end()) {
				break;
			}
		}
	}

	Monster_BulletList->LateUpdate(fDeltaTime);
	std::cout << Monster_BulletList->GetBulletList()->size() << std::endl;

	return 0;
}


void CScene::Collision(float fDeltaTime)
{

	for (CItem* Item : m_ItemList) {
		if (m_Player1 && CCore::GetInst()->m_hPlayer1) {
			if (Item->Collision(fDeltaTime, m_Player1->GetPos(), m_Player1->GetSize()))
			{
				Item->SetDestroy();
			}
		}
		if (m_Player2 && CCore::GetInst()->m_hPlayer2) {
			if (Item->Collision(fDeltaTime, m_Player2->GetPos(), m_Player2->GetSize()))
			{
				Item->SetDestroy();
			}
		}
	}

	for (CMonster* Monster : *m_MonsterList)
	{
		if (m_Player1 && CCore::GetInst()->m_hPlayer1 && (Monster->GetObjectState() == OBJECT_STATE::IDLE || Monster->GetIsDie())) {
			// 몬스터 - 플레이어 총알
			if (m_Player1->GetmyBulletList()->Collision(fDeltaTime, Monster->GetPos(), Monster->GetSize()))
			{
				//std::cout << "Player1 불렛, 몬스터 충돌" << std::endl;
			}
			// 몬스터 - 플레이어
			if (m_Player1->Collision(fDeltaTime, Monster->GetPos(), Monster->GetSize()))
			{
				//std::cout << "Player1, 몬스터 충돌" << std::endl;
			}
		}

		if (m_Player2 && CCore::GetInst()->m_hPlayer2 && (Monster->GetObjectState() == OBJECT_STATE::IDLE || Monster->GetIsDie())) {
			// 몬스터 - 플레이어 총알
			if (m_Player2->GetmyBulletList()->Collision(fDeltaTime, Monster->GetPos(), Monster->GetSize()))
			{
				//std::cout << "Player2 불렛, 몬스터 충돌" << std::endl;
			}
			// 몬스터 - 플레이어
			if (m_Player2->Collision(fDeltaTime, Monster->GetPos(), Monster->GetSize()))
			{
				//std::cout << "Player2, 몬스터 충돌" << std::endl;
			}
		}
	}


	// 몬스터 총알 - 플레이어
	if (m_Player1 && CCore::GetInst()->m_hPlayer1) {
		if (Monster_BulletList->Collision(fDeltaTime, m_Player1->GetPos(), m_Player1->GetSize()))
		{
			//std::cout << "Player1, 몬스터 불렛 충돌" << std::endl;
		}
	}
	if (m_Player2 && CCore::GetInst()->m_hPlayer2) {
		if (Monster_BulletList->Collision(fDeltaTime, m_Player2->GetPos(), m_Player2->GetSize()))
		{
			//std::cout << "Player2, 몬스터 불렛 충돌" << std::endl;
		}
	}

}

void CScene::UpdateBulletListWithBoss()
{
	if (m_boss) {
		std::list<CBullet*>* bulletList = m_boss->GetBulletList()->GetBulletList();

		for (CBullet* bullet : *bulletList) {
			Monster_BulletList->GetBulletList()->push_back(bullet);
		}
		bulletList->clear();
	}
}

void CScene::UpdateMaxDistance(double distance)
{
	m_Distance += distance;
	//if (m_Distance >= m_MaxDistance)
	//{
	//	m_bEndScene = true;

	//	//// ���� �������� ����� �����մϴ�..
	//	//this->m_bEnable = false;
	//	//// ���� ���������� ����ϰ� �մϴ�...
	//	//NextScene->SetEnable(true);
	//	//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 2);
	//}
}




