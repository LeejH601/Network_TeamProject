#include "../Include/Game.h"
#include "../Object/Player.h"
#include "../Object/Item.h"
#include "../Object/Monster.h"
#include "..\Object\Boss.h"
#include "../Object/BulletList.h"
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
			(*it)->CreateBullet(&Monster_BulletList);
		}
	}

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
    fItemSpawn -= (fDeltaTime * 300.0f);

	if (fItemSpawn < FLT_EPSILON)
	{
		CItem* pItem = new CItem;
		pItem->Init(OBJECT_TYPE::IT_RANDOM, { 1.f + rand() % 600, 30 });
		m_ItemList.push_back(pItem);

		fItemSpawn = 500.0f;
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

			}
			else if (m_StageNum == 2)
			{
				m_boss->Init(POSITION{ 300,100 }, OBJECT_TYPE::OBJ_BOSS_TWO, { 0,1 }, m_StageNum);

			}
			else if (m_StageNum == 3)
			{
				m_boss->Init(POSITION{ 300,100 }, OBJECT_TYPE::OBJ_BOSS_THREE, { 0,1 }, m_StageNum);

			}
		}
	}


	// Need To Delete
	else
	{
		UpdateMaxDistance(fDeltaTime * 300.0f);
		if (m_Distance >= m_MaxDistance)
		{
			m_bEndScene = true;
		}
	}

	if (!m_ItemList.empty())
	{
		for (std::list<CItem*>::iterator lBegin = m_ItemList.begin();
			lBegin != m_ItemList.end(); ++lBegin)
		{
			if ((*lBegin))
				(*lBegin)->Update(fDeltaTime * 300.0f);
		}
	}

	//if (m_Player)
	//{

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
			(*it)->~CMonster();
			delete* it;
			it = m_MonsterList->erase(it);
			if (it != m_MonsterList->begin())
				it--;
			else if (it == m_MonsterList->end()) {
				break;
			}
		}
	}


	for (auto it = m_ItemList.begin(); it != m_ItemList.end();) {
		if ((*it)->GetObjectState() == OBJECT_STATE::ERASE) {
			auto temp = *it;
			it++;
			m_ItemList.remove(temp);
			delete temp;
		}
		else
			it++;
	}

	return 0;
}


void CScene::Collision(float fDeltaTime)
{

	for (CItem* Item : m_ItemList) {
		if (m_Player1) {
			Item->Collision(fDeltaTime, m_Player1->GetPos(), m_Player1->GetSize());
		}
		if (m_Player2) {
			Item->Collision(fDeltaTime, m_Player2->GetPos(), m_Player2->GetSize());
		}
	}


	//if (m_Player == nullptr)
	//	return;


	//if (m_Player)
	//	m_Player->Collision(fDeltaTime, { 0,0 }, { 0,0 });


	//// ���Ϳ� �÷��̾��� �Ѿ˰� �浹üũ �մϴ�...
	//for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++)
	//{
	//	if ((*it)->GetState() == MONSTER_STATE::DONDESTORY || (*it)->GetIsDie() == true)
	//		continue;
	//	// ���Ϳ� �÷��̾� �Ѿ˰� �浹üũ �մϴ�... 
	//	(*it)->Collision(fDeltaTime, m_Player->GetmyBulletList());

	//	// �浹 �� ������ ���°� DESTROY �̸� �����մϴ�...
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
	//	// ������ �׾��ٸ� 
	//	m_boss->Collision(fDeltaTime, m_Player->GetmyBulletList());
	//	//	m_bEndScene = true;
	//	if (m_boss->GetState() == MONSTER_STATE::DESTORY)
	//		m_bEndScene = true;

	//}

	//// �÷��̾�� ���� �Ѿ˰� �浹üũ �մϴ�...
	//if (m_Player)
	//{
	//	m_Player->Collision(fDeltaTime, Monster_BulletList);

	//	// ������ �Ѿ˰� �浹üũ �մϴ�...
	//	if (m_boss)
	//		m_Player->Collision(fDeltaTime, m_boss->GetMyBulletList());

	//	// Ʈ���� ���� �扟üũ �մϴ�... 
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



	//	// �����۰��� �浹 üũ 

	//	if (m_ItemList)
	//		m_ItemList->Collision(fDeltaTime, m_Player->GetPos(), m_Player->GetSize(), m_Player);
	//}
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




