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
			NextStageNum = 2;

		}

	}
	else if (m_Scene_stage2->GetEnable())
	{
		if (m_Scene_stage2->Update(fDeltaTime) == 1)
		{
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(true);
			NextStageNum = 3;
		}
	}

	else if (m_Scene_stage3->GetEnable())
	{
		if (m_Scene_stage3->Update(fDeltaTime) == 1)
		{
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(true);
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

std::list<CItem*>* CSceneManager::GetItemlistFromSceneType(SCENE_TYPE type)
{
	CScene* scene;
	switch (type)
	{
	case SCENE_TYPE::ST_BEGIN:
		scene = m_Scene_Begin;
		break;
	case SCENE_TYPE::ST_STAGE1:
		scene = m_Scene_Stage1;
		break;
	case SCENE_TYPE::ST_STAGE2:
		scene = m_Scene_stage2;
		break;
	case SCENE_TYPE::ST_STAGE3:
		scene = m_Scene_stage3;
		break;
	case SCENE_TYPE::ST_CLEAR:
		scene = m_Scene_StageClear;
		break;
	case SCENE_TYPE::ST_END:
		scene = m_Scene_End;
		break;
	default:
		scene = nullptr;
		break;
	}
	if (scene)
		return scene->GetItemList();
	return nullptr;
}


SCENE_TYPE CSceneManager::GetCurrentSceneType()
{
	if (m_Scene_Begin->GetEnable())
		return SCENE_TYPE::ST_BEGIN;
	if (m_Scene_Stage1->GetEnable())
		return SCENE_TYPE::ST_STAGE1;
	if (m_Scene_stage2->GetEnable())
		return SCENE_TYPE::ST_STAGE2;
	if (m_Scene_stage3->GetEnable())
		return SCENE_TYPE::ST_STAGE3;
	if (m_Scene_End->GetEnable())
		return SCENE_TYPE::ST_END;
	if (m_Scene_StageClear->GetEnable())
		return SCENE_TYPE::ST_CLEAR;
	return SCENE_TYPE(-1);
}

bool CSceneManager::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_clientReady:
	{
		if (!CCore::GetInst()->m_hPlayer2)
		{
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(true);
		}
	}
	return true;
	default:
		break;
	}

	return false;
}
