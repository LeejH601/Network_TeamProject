#include "SceneManager.h"
#include "Scene.h"
#include "../Core.h"
#include "../Network/NetworkDevice.h"
#include "../Locator.h"

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

	SAFE_DELETE(m_Player);
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

	// Player ���� ����X
	//m_Player = new CPlayer;
	//m_Player->Init();

	//m_Scene_End->Init(m_Player,false);
	//m_Scene_stage3->Init(m_Player,false);


	return true;
}

void CSceneManager::Update(float fDeltaTime)
{
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Update(fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
	{
		// �ش� ���� ����� == 1 
		if (m_Scene_Stage1->Update(fDeltaTime) == 1)
		{
			m_Scene_Stage1->SetEnable(false);
			// �������� ����ǵ��� �մϴ�...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
			NextStageNum = 2;

		}

	}
	else if (m_Scene_StageClear->GetEnable())
	{
		m_StageClearCount += 1;
		if (m_StageClearCount == 3000)
		{
			m_StageClearCount = 0;
			switch (NextStageNum)
			{

			case 2:
				m_Scene_StageClear->SetEnable(false);
				m_Scene_stage2->SetEnable(true);
				//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 2);
				break;
			case 3:
				m_Scene_StageClear->SetEnable(false);
				m_Scene_stage3->SetEnable(true);
				//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 3);
				break;
			case 0:
				m_Scene_StageClear->SetEnable(false);
				m_Scene_End->SetEnable(true);
				//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 0);


			default:
				break;
			}
		}

	}

	else if (m_Scene_stage2->GetEnable())
	{
		if (m_Scene_stage2->Update(fDeltaTime) == 1)
		{
			m_Scene_stage2->SetEnable(false);
			// �������� ����ǵ��� �մϴ�...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
			NextStageNum = 3;


		}
	}

	else if (m_Scene_stage3->GetEnable())
	{
		if (m_Scene_stage3->Update(fDeltaTime) == 1)
		{
			m_Scene_stage3->SetEnable(false);
			// �������� ����ǵ��� �մϴ�...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			//CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
			NextStageNum = 0;

		}
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

CPlayer* CSceneManager::GetPlayer()
{
	return m_Player;
}

bool CSceneManager::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_clientReady:
	{
		Telegram tel_Checked;
		tel_Checked.Receiver = 0;
		tel_Checked.Msg = (int)MESSAGE_TYPE::Msg_changeScene;
		tel_Checked.Extrainfo = new int;
		
		SCENE_TYPE st_Begin = SCENE_TYPE::ST_STAGE1;
		if (m_Scene_Stage1)
			m_Scene_Stage1->SetEnable(true);
		memcpy(tel_Checked.Extrainfo, &st_Begin, sizeof(SCENE_TYPE));

		auto cs = client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second;
        EnterCriticalSection(&cs);

		CNetworkDevice* p;
		if (!CCore::GetInst()->m_hPlayer2)
			p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
		else
			p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);

		p->AddMessage(tel_Checked);
		LeaveCriticalSection(&cs);
	}
		break;
	default:
		break;
	}

	return false;
}
