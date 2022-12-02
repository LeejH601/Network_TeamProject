#include "Core.h"
#include "Core/Timer.h"
#include "Scene/SceneManager.h"
#include "MessageDispatcher/CMessageDispatcher.h"
#include "Object/Monster.h"
#include "Network/NetworkDevice.h"
#include "Locator.h"
#include "Object/Item.h"
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
	LateUpdate(fDeltaTime);		// * ������Ʈ ��ó�� 
	Collision(fDeltaTime);		// * �浹 ó��

	CMessageDispatcher::GetInst()->DispatchMessages();

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

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	if (CSceneManager::GetInst())
		CSceneManager::GetInst()->Collision(fDeltaTime);
	//std::cout << "Server Collision" << std::endl;
}

void CCore::SnapshotInit(int nPlayer)
{
	// 플레이어 핸들
	DWORD hPlayer = (nPlayer == 0) ? m_hPlayer1 : m_hPlayer2;

	auto GenerateMsgCreate = [](DWORD hP, CObject* obj) {

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

		
		CNetworkDevice* p;
		p = Locator.GetNetworkDevice(hP);
		p->AddMessage(telegram);
		

		delete[] telegram.Extrainfo;
	};

	// 임계영역 진입 - 안전을 위해 모든 메시지 적재 작업 완료 후 임계영역 탈출
	CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(hPlayer, nullptr))->second);
	EnterCriticalSection(&c_cs);

	CSceneManager* SCM = CSceneManager::GetInst();
	// 씬 메시지
	SCM->SendMsgChangeScene(SCM->GetCurrentSceneType());
	// 플레이어 생성 메시지
	

	// 몬스터 생성 메시지
	std::list<CMonster*>* mob_list =  SCM->GetMonsterList();
	for (CMonster* mob : *mob_list) {
		GenerateMsgCreate(hPlayer, mob);
	}
	// 아이템 생성 메시지
	std::list<CItem*>* item_list = SCM->GetItemlistFromSceneType(SCM->GetCurrentSceneType());
	for (CItem* item : *item_list) {
		GenerateMsgCreate(hPlayer, item);
	}

	// 블릿 생성 메시지


	LeaveCriticalSection(&c_cs);
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