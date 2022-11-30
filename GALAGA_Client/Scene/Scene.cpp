#include "../Include/Game.h"
#include "../Object/Item.h"
#include "../Object/Player.h"
#include "../Object/BulletList.h"
#include "../Scene/SceneManager.h"
#include "Scene.h"

CScene::CScene() : m_bEnable(false), m_bSlide(false)
{
}

CScene::~CScene()
{
	Monster_BulletList->EraseAll();
	delete Monster_BulletList;
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
	float fMovedistY = fDeltaTime * 200 * 1.8f;

	if (m_imgLT.y <= 0)
	{
		m_imgLT.y = 0;
		m_bSlide = true;
	}
	if (m_bSlide == true)
	{
		// proto Img
		m_imgRenderLT.y += fMovedistY;
		m_imgRenderSize.y -= fMovedistY;

		m_imgLT.y = 0;
		m_imgSize.y -= fMovedistY;

		// Second Img
		m_imgRenderLT2.y = 0;
		m_imgRenderSize2.y = (750 - m_imgRenderSize.y) + 1;

		m_imgLT2.y -= fMovedistY;
		m_imgSize2.y += fMovedistY;

		if (m_imgRenderSize.y <= 1)
		{
			m_bSlide = false;

			// proto init
			m_imgLT.y = 4000 - 750;
			m_imgSize.y = 750;

			m_imgRenderLT.y = 0;
			m_imgRenderSize.y = 750;

			//second init
			m_imgRenderSize2.y = 1;
			m_imgLT2.y = 4000;
			m_imgSize2.y = 1;
		}
	}
	else
	{
		m_imgLT.y -= fMovedistY;
	}
}

void CScene::imgLT_Move_Auto(float fDeltaTime)
{
	float fMovedistY = fDeltaTime * 200 * 1.7;
	if (m_imgLT.y <= 0)
	{
		m_imgLT.y = 0;
		m_bSlide = true;
	}
	if (m_bSlide == true)
	{
		// proto Img
		m_imgRenderLT.y += fMovedistY;
		m_imgRenderSize.y -= fMovedistY;

		m_imgLT.y = 0;
		m_imgSize.y -= fMovedistY;

		// Second Img
		m_imgRenderLT2.y = 0;
		m_imgRenderSize2.y = (750 - m_imgRenderSize.y) + 1;

		m_imgLT2.y -= fMovedistY;
		m_imgSize2.y += fMovedistY;

		if (m_imgRenderSize.y <= 1)
		{
			m_bSlide = false;

			// proto init
			m_imgLT.y = 4000 - 750;
			m_imgSize.y = 750;

			m_imgRenderLT.y = 0;
			m_imgRenderSize.y = 750;

			//second init
			m_imgRenderSize2.y = 1;
			m_imgLT2.y = 4000;
			m_imgSize2.y = 1;
		}
	}
	else
	{
		m_imgLT.y -= fMovedistY;
	}
}

void CScene::Set_MainPlayer(CPlayer* pPlayer)
{
	m_MainPlayer = pPlayer;
}

void CScene::Set_AnotherPlayer(CPlayer* pPlayer)
{
	m_AnotherPlayer = pPlayer;
}

bool CScene::Init(const WCHAR* imgBackText, CPlayer* mainplayer, CPlayer* anotherplayer, long long MaxDistance, bool enable, int stageNum)
{
	m_StageNum = stageNum;

	//if (player != nullptr)
	//{
	//	m_ItemList = new CItemList;
	//	m_ItemList->Init();
	//}
	auto rst = m_BackImage.Load(imgBackText);

	// Load Fail -> ���ѷ��� 
	if (S_OK != rst) {
		while (true);
	}

	m_MainPlayer = mainplayer;
	m_AnotherPlayer = anotherplayer;

	m_MaxDistance = MaxDistance;
	m_bEnable = enable;
	m_bEndScene = false;

	m_imgLT.x = 0;
	m_imgLT.y = 0;
	m_imgSize.x = 600;
	m_imgSize.y = 750;

	m_imgRenderLT.x = 0;
	m_imgRenderLT.y = 0;
	m_imgRenderSize.x = 600;
	m_imgRenderSize.y = 750;

	m_imgLT2.x = 0;
	m_imgLT2.y = 4000;
	m_imgSize2.x = 600;
	m_imgSize2.y = 1;

	m_imgRenderLT2.x = 0;
	m_imgRenderLT2.y = 0;
	m_imgRenderSize2.x = 600;
	m_imgRenderSize2.y = 1;

	// ���带 ����մϴ�. 
	//PlaySound(TEXT("./Sound/Terran_Theme1.mp3"), NULL, SND_ASYNC | SND_LOOP);

	//if (player != nullptr)
	//{
	//	m_MonsterList = CSceneManager::GetInst()->GetMonsterList();
	//	Monster_BulletList = new CBulletList;
	//	Monster_BulletList->Init();
	//}


	m_MonsterList = CSceneManager::GetInst()->GetMonsterList();
	Monster_BulletList = new CBulletList;



	return true;
}

void CScene::AddObject(int id, OBJECT_TYPE obj_Type, POSITION pos)
{
	if ((int)obj_Type < 10000)
	{
		CItem* pItem = new CItem;
		pItem->Init(obj_Type, pos);
		pItem->RegisterObject(id);
		m_ItemList.push_back(pItem);
	}

	else if ((int)obj_Type > 10000 && (int)obj_Type < 40000)
	{
		// Monster
		CMonster* t_mon = new CMonster;
		t_mon->Init(pos, Pattern(m_StageNum), obj_Type, POSITION(0, 1), m_StageNum);
		t_mon->RegisterObject(id);
		m_MonsterList->push_back(t_mon);
	}

	else if ((int)obj_Type == 40001)
	{
		// Bullet
		Monster_BulletList->AddBullet(id, pos, _SIZE(10, 10), POSITION(0.f, 1.f), 20.f);
		Monster_BulletList->SetAttack(50.f);
	}

	else if ((int)obj_Type > 40001 && (int)obj_Type < 50000) // Player Bullet
	{
		m_MainPlayer->GetmyBulletList()->AddBullet(id, pos, m_MainPlayer->GetSize(), 800.f);
	}


}

void CScene::Input(float fDeltaTime, CScene* NextScene)
{
	if (m_MainPlayer)
		m_MainPlayer->Input(fDeltaTime);
}

int CScene::Update(float fDeltaTime)
{
	if (m_MainPlayer)
		m_MainPlayer->Update(fDeltaTime);

	/*m_Player->Update(fDeltaTime);*/
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	return 0;
}


void CScene::Collision(float fDeltaTime)
{

}

void CScene::Render(HDC mainhDC, HDC hDC, float fDeltaTime)
{

	// ��� ���
	if (m_bSlide == true)
	{
		// Back Image Render 
		m_BackImage.Draw(hDC, m_imgRenderLT.x, m_imgRenderLT.y, m_imgRenderSize.x, m_imgRenderSize.y,
			m_imgLT.x, m_imgLT.y, m_imgSize.x, m_imgSize.y);

		// Back Image Render 
		m_BackImage.Draw(hDC, m_imgRenderLT2.x, m_imgRenderLT2.y, m_imgRenderSize2.x, m_imgRenderSize2.y,
			m_imgLT2.x, m_imgLT2.y, m_imgSize2.x, m_imgSize2.y);

	}

	else if (m_bSlide == false)
	{
		// Back Image Render 
		m_BackImage.Draw(hDC, m_imgRenderLT.x, m_imgRenderLT.y, m_imgRenderSize.x, m_imgRenderSize.y,
			m_imgLT.x, m_imgLT.y, m_imgSize.x, m_imgSize.y);
	}

	for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
		(*it)->Render(mainhDC, hDC, fDeltaTime);
	}
	if (Monster_BulletList)
		Monster_BulletList->RenderAll(mainhDC, hDC, fDeltaTime);
	if (m_MainPlayer)
	{
		m_MainPlayer->Render(mainhDC, hDC, fDeltaTime);
		//for (list<CMonster*>::iterator it = m_MonsterList->begin(); it != m_MonsterList->end(); it++) {
		//	(*it)->Render(mainhDC, hDC, fDeltaTime);
		//}
		//// ���� �Ѿ� ���
		//Monster_BulletList->RenderAll(mainhDC, hDC, fDeltaTime);

		//// ������ ���
		//if (m_boss != nullptr) {
		//	m_boss->Render(mainhDC, hDC, fDeltaTime);
		//}
		//// Ʈ���� ���
		//if (m_Tractor != nullptr) {
		//	m_Tractor->Render(mainhDC, hDC, fDeltaTime);
		//}

	}

	if (m_AnotherPlayer)
	{
		m_AnotherPlayer->Render(mainhDC, hDC, fDeltaTime);
	}

	for (auto i = m_ItemList.begin();
		i != m_ItemList.end(); ++i)
		(*i)->Render(mainhDC, hDC, fDeltaTime);

	// MemDc �� �ִ� ȭ���� main HDC �� ����մϴ�... < ���� ��� >
	BitBlt(mainhDC, 0, 0, 600, 750, hDC, 0, 0, SRCCOPY);

}

void CScene::UpdateMaxDistance(double distance, CScene* NextScene)
{



}