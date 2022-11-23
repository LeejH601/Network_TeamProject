#include "SceneManager.h"
#include "Scene.h"
#include "../Core/Timer.h"
#include "../Core.h"
#include "../Network/NetworkDevice.h"
#include "../Locator.h"
#include "../Object/Player.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_Scene_Begin);
	SAFE_DELETE(m_Scene_End);
	SAFE_DELETE(m_Scene_Stage1);
	SAFE_DELETE(m_Scene_stage2);
	SAFE_DELETE(m_Scene_stage3);

	SAFE_DELETE(m_Scene_End1);
	SAFE_DELETE(m_Scene_End2);
	SAFE_DELETE(m_Scene_End3);

	SAFE_DELETE(m_Scene_StageClear);

	SAFE_DELETE(m_Player1);
	SAFE_DELETE(m_Player2);
}

bool CSceneManager::Init()
{
	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	m_Scene_Begin = new CScene;
	m_Scene_End = new CScene;
	m_Scene_Stage1 = new CScene;
	m_Scene_stage2 = new CScene;
	m_Scene_stage3 = new CScene;
	m_Scene_StageClear = new CScene;

	m_Scene_End1 = new CScene;
	m_Scene_End2 = new CScene;
	m_Scene_End3 = new CScene;


	m_Player1 = new CPlayer;
	m_Player2 = new CPlayer;
	m_Player1->Init();
	m_Player2->Init();
	
	// Init Scene
	m_Scene_Begin->Init(nullptr, nullptr, 0, true, 0);
	m_Scene_Stage1->Init(m_Player1, m_Player2, 8000, false, 1);
	m_Scene_stage2->Init(m_Player1, m_Player2, 8000, false, 2);
	m_Scene_stage3->Init(m_Player1, m_Player2, 8000, false, 3);
	m_Scene_StageClear->Init(nullptr, nullptr, 0, false, 0);
	m_Scene_End->Init(nullptr, nullptr, 0, false, 0);

	return true;
}

void CSceneManager::Update(float fDeltaTime)
{

	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Update(fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
	{

		if (m_Scene_Stage1->Update(fDeltaTime))
		{
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(true);
			SendMsgChangeScene(SCENE_TYPE::ST_STAGE2);
			NextStageNum = 2;

		}

	}
	else if (m_Scene_stage2->GetEnable())
	{
		if (m_Scene_stage2->Update(fDeltaTime) == 1)
		{
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(true);
			SendMsgChangeScene(SCENE_TYPE::ST_STAGE3);
			NextStageNum = 3;
		}
	}

	else if (m_Scene_stage3->GetEnable())
	{
		if (m_Scene_stage3->Update(fDeltaTime) == 1)
		{
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(true);
			SendMsgChangeScene(SCENE_TYPE::ST_CLEAR);
			NextStageNum = 0;
		}
	}
	else if (m_Scene_StageClear->GetEnable())
	{
	}

	else if (m_Scene_End->GetEnable())
		m_Scene_End->Update(fDeltaTime);
}

void CSceneManager::LateUpdate(float fDeltaTime)
{
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->LateUpdate(fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
		m_Scene_Stage1->LateUpdate(fDeltaTime);

	else if (m_Scene_stage2->GetEnable())
		m_Scene_stage2->LateUpdate(fDeltaTime);

	else if (m_Scene_stage3->GetEnable())
		m_Scene_stage3->LateUpdate(fDeltaTime);

	else if (m_Scene_End->GetEnable())
		m_Scene_End->LateUpdate(fDeltaTime);
}

void CSceneManager::Collision(float fDeltaTime)
{
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Collision(fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
		m_Scene_Stage1->Collision(fDeltaTime);

	else if (m_Scene_stage2->GetEnable())
		m_Scene_stage2->Collision(fDeltaTime);

	else if (m_Scene_stage3->GetEnable())
		m_Scene_stage3->Collision(fDeltaTime);

	else if (m_Scene_End->GetEnable())
		m_Scene_End->Collision(fDeltaTime);
}

CPlayer* CSceneManager::GetPlayer1()
{
	return m_Player1;
}

CPlayer* CSceneManager::GetPlayer2()
{
	return m_Player2;
}


void CSceneManager::SendMsgChangeScene(SCENE_TYPE nType)
{
	Telegram tel_ChangeScene;
	tel_ChangeScene.Sender = 0;
	tel_ChangeScene.Receiver = 0;
	tel_ChangeScene.DispatchTime = CTimer::GetInst()->GetTime();
	tel_ChangeScene.Msg = (int)MESSAGE_TYPE::Msg_changeScene;
	tel_ChangeScene.Extrainfo = new char[4];
	int scene_type = (int)nType;

	memcpy(tel_ChangeScene.Extrainfo, &scene_type, sizeof(SCENE_TYPE));

	CObject::SendMessageToClient(tel_ChangeScene);
}

bool CSceneManager::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_clientReady:
	{
		Telegram tel_Checked;
		tel_Checked.Sender = m_iObjID;
		tel_Checked.Receiver = 0;
		tel_Checked.DispatchTime = CTimer::GetInst()->GetTime();
		tel_Checked.Msg = (int)MESSAGE_TYPE::Msg_changeScene;
		tel_Checked.Extrainfo = new int;
		SCENE_TYPE st_Begin = SCENE_TYPE::ST_STAGE1;
		memcpy(tel_Checked.Extrainfo, &st_Begin, sizeof(SCENE_TYPE));

		if (!CCore::GetInst()->m_hPlayer2)
		{
			CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second);
			EnterCriticalSection(&c_cs);
			CNetworkDevice* p;
			p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
			p->AddMessage(tel_Checked);
			LeaveCriticalSection(&c_cs);

			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(true);
		}
		else
		{
			CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer2, nullptr))->second);
			EnterCriticalSection(&c_cs);
			CNetworkDevice* p;
			p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);
			p->AddMessage(tel_Checked);
			LeaveCriticalSection(&c_cs);
		}
	}
	return true;
	default:
		break;
	}

	return false;
}
