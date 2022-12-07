#include "Core.h"
#include "Core/Timer.h"
#include "Scene/SceneManager.h"
#include "MessageDispatcher/CMessageDispatcher.h"
#include "Object/Monster.h"
#include "Network/NetworkDevice.h"
#include "Locator.h"
#include "Object/Item.h"
#include "Object/Player.h"
#include "Object/Bullet.h"
#include "Object/BulletList.h"
//#include "Sound/SoundManager.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

CCore::CCore()
{

}


CCore::~CCore()
{
	//DESTROY_SINGLE(CSoundManager);
	//DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CTimer);
}

// Game ���� ���� �Լ����Դϴ�. ***

void CCore::Logic()
{
	// ��ŸŸ���� ������ �� ����ϴ�. 
	GET_SINGLE(CTimer)->Update();
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
	// fDeltaTime_update = GET_SINGLE(CTimer)->GetTimer_Update();

	Update(fDeltaTime);			// * ������Ʈ
	EnterCriticalSection(&main_loop_cs);
	LateUpdate(fDeltaTime);		// * ������Ʈ ��ó�� 
	LeaveCriticalSection(&main_loop_cs);
	Collision(fDeltaTime);		// * �浹 ó��
}


int CCore::Update(float fDeltaTime)
{
	//std::cout << "Server Update" << std::endl;
	if (CSceneManager::GetInst())
		CSceneManager::GetInst()->Update(fDeltaTime);

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	//std::cout << "Server LateUpdate" << std::endl;
	if (CSceneManager::GetInst())
		CSceneManager::GetInst()->LateUpdate(fDeltaTime);

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	if (CSceneManager::GetInst())
		CSceneManager::GetInst()->Collision(fDeltaTime);
	//std::cout << "Server Collision" << std::endl;
}

void CCore::SnapshotRun(DWORD hPlayer)
{
	CNetworkDevice* p;
	p = Locator.GetNetworkDevice(hPlayer);
	p->GetTelegram();

	CMessageDispatcher::GetInst()->DispatchMessages();

	auto GenerateMsgCreate = [](CNetworkDevice* network, CObject* obj) {

		Telegram telegram;
		telegram.Sender = obj->GetID();
		telegram.Receiver = 0;
		telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
		telegram.DispatchTime = CTimer::GetInst()->GetTime();
		telegram.Extrainfo = new char[sizeof(int) + sizeof(POSITION)];
		OBJECT_TYPE type = obj->GetObjType();
		memcpy(telegram.Extrainfo, &type, sizeof(int));
		POSITION pos = obj->GetPos();
		memcpy((char*)telegram.Extrainfo + sizeof(int), &pos, sizeof(POSITION));

		network->AddMessage(telegram);

		delete[] telegram.Extrainfo;
	};
	
	auto GenerateMsgMove = [](CNetworkDevice* network, CObject* obj) {
		Telegram telegram;
		telegram.Sender = obj->GetID();
		telegram.Receiver = obj->GetID();
		telegram.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
		telegram.DispatchTime = CTimer::GetInst()->GetTime();
		telegram.Extrainfo = new char[sizeof(POSITION)];

		POSITION pos = obj->GetPos();
		memcpy((char*)telegram.Extrainfo, &pos, sizeof(POSITION));

		network->AddMessage(telegram);

		delete[] telegram.Extrainfo;
	};

	auto GenerateMsgChangeScene = [](CNetworkDevice* network) {

		Telegram telegram;
		telegram.Sender = 0;
		telegram.Receiver = 0;
		telegram.DispatchTime = CTimer::GetInst()->GetTime();
		telegram.Msg = (int)MESSAGE_TYPE::Msg_changeScene;
		telegram.Extrainfo = new char[4];

		int current_Scene = (int)CSceneManager::GetInst()->GetCurrentSceneType();
		
		memcpy(telegram.Extrainfo, &current_Scene, sizeof(SCENE_TYPE));

		network->AddMessage(telegram);
		delete[] telegram.Extrainfo;
	};

	auto GenerateMsgChangeState = [](CNetworkDevice* network, CObject* obj) {

		Telegram telegram;
		telegram.Sender = obj->GetID();
		telegram.Receiver = obj->GetID();
		telegram.DispatchTime = CTimer::GetInst()->GetTime();
		telegram.Msg = (int)MESSAGE_TYPE::Msg_objectChangeState;
		telegram.Extrainfo = new char[4];

		int current_State = (int)(obj->GetObjectState());

		memcpy(telegram.Extrainfo, &current_State, sizeof(OBJECT_TYPE));

		network->AddMessage(telegram);
		delete[] telegram.Extrainfo;
	};

	CSceneManager* SCM = CSceneManager::GetInst();

	// 씬 메시지
	GenerateMsgChangeScene(p);

	// 플레이어 생성 메시지
	if (CCore::GetInst()->m_hPlayer1 == hPlayer)
	{
		((CObject*)SCM->GetPlayer1())->SetObjType(OBJECT_TYPE::OBJ_PLAYER);
		GenerateMsgCreate(p, (CObject*)SCM->GetPlayer1());
		if (CCore::GetInst()->m_hPlayer2)
		{
			((CObject*)SCM->GetPlayer2())->SetObjType(OBJECT_TYPE::OBJ_ANOTHER_PLAYER);
			GenerateMsgCreate(p, (CObject*)SCM->GetPlayer2());
			GenerateMsgMove(p, (CObject*)SCM->GetPlayer2());
		}
	}

	if (CCore::GetInst()->m_hPlayer2 == hPlayer)
	{
		((CObject*)SCM->GetPlayer2())->SetObjType(OBJECT_TYPE::OBJ_PLAYER);
		GenerateMsgCreate(p, (CObject*)SCM->GetPlayer2());
		if (CCore::GetInst()->m_hPlayer1)
		{
			((CObject*)SCM->GetPlayer1())->SetObjType(OBJECT_TYPE::OBJ_ANOTHER_PLAYER);
			GenerateMsgCreate(p, (CObject*)SCM->GetPlayer1());
			GenerateMsgMove(p, (CObject*)SCM->GetPlayer1());
		}
	}

	// 몬스터 생성 메시지
	std::list<CMonster*>* mob_list = SCM->GetMonsterList();

	for (CMonster* mob : *mob_list) {
		GenerateMsgCreate(p, mob);
		GenerateMsgMove(p, mob);
	}

	// 아이템 생성 메시지
	std::list<CItem*>* item_list = SCM->GetItemlistFromSceneType(SCM->GetCurrentSceneType());
	for (CItem* item : *item_list) {
		if (item->GetObjectState() == OBJECT_STATE::IDLE)
		{
			GenerateMsgCreate(p, item);
			GenerateMsgMove(p, item);
		}
		GenerateMsgChangeState(p, item);
	}

	// 블릿 생성 메시지
	if (CCore::GetInst()->m_hPlayer1)
	{
		CBulletList* pPlayerBulletList = (SCM->GetPlayer1())->GetmyBulletList();
		for (CBullet* pBullet : *(pPlayerBulletList->GetBulletList())) {
			GenerateMsgCreate(p, pBullet);
			GenerateMsgMove(p, pBullet);
		}
	}

	if (CCore::GetInst()->m_hPlayer2)
	{
		CBulletList* pPlayerBulletList = (SCM->GetPlayer2())->GetmyBulletList();
		for (CBullet* pBullet : *(pPlayerBulletList->GetBulletList())) {
			GenerateMsgCreate(p, pBullet);
			GenerateMsgMove(p, pBullet);
		}
	}
	// 플레이어 무브 메시지

}

bool CCore::Init()
{
	// �ػ� ����
	m_tRS.iW = 600;
	m_tRS.iH = 750;


	// Ÿ�̸Ӹ� �ʱ�ȭ �մϴ�. 
	if (!CTimer::GetInst()->Init())
		return false;

	// ��� �����ڸ� �ʱ�ȭ �մϴ�. 
	if (!CSceneManager::GetInst()->Init())
		return false;

	// ���� �Ŵ����� �ʱ�ȭ �մϴ�.

	return true;
}

int CCore::Run()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�
	while (m_bLoop)
	{
		// ���ӱ��� logic �� �����˴ϴ�.
		Logic();
	}

	return 1;
}