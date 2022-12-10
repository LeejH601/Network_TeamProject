#include "../Sound/SoundManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../Object/Player.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{

	for (int i = 0; i < 19; ++i)
	{
		if (images[i])
			images[i].Destroy();
	}
	SAFE_DELETE(m_Scene_Begin);
	SAFE_DELETE(m_Scene_End);
	SAFE_DELETE(m_Scene_Stage1);
	SAFE_DELETE(m_Scene_stage2);
	SAFE_DELETE(m_Scene_stage3);

	SAFE_DELETE(m_Scene_End1);
	SAFE_DELETE(m_Scene_End2);
	SAFE_DELETE(m_Scene_End3);

	SAFE_DELETE(m_Scene_StageClear);

	SAFE_DELETE(m_MainPlayer);
	SAFE_DELETE(m_AnotherPlayer);
}

bool CSceneManager::Init()
{

	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);


	wcscpy_s(m_img_Text[0], L"../Image/Item_img/Bullets.png");
	wcscpy_s(m_img_Text[1], L"../Image/Item_img/icon_ATKSPDUP.png");
	wcscpy_s(m_img_Text[2], L"../Image/Item_img/icon_HPUP.png");
	wcscpy_s(m_img_Text[3], L"../Image/Item_img/icon_INVINCIBILITY.png");
	wcscpy_s(m_img_Text[4], L"../Image/Item_img/icon_PowUp.png");

	wcscpy_s(m_img_Text[5], L"../Image/Terran_img/Wraith.png");;
	wcscpy_s(m_img_Text[6], L"../Image/Terran_img/Valkyrie.png");;
	wcscpy_s(m_img_Text[7], L"../Image/Terran_img/Battle Cruiser.png");;
	wcscpy_s(m_img_Text[8], L"../Image/Terran_img/Dropship.png");;
	wcscpy_s(m_img_Text[9], L"../Image/Terran_img/Vessel.png");;
	wcscpy_s(m_img_Text[10], L"../Image/Zerg_img/Mutalisk.png");;
	wcscpy_s(m_img_Text[11], L"../Image/Zerg_img/Queen.png");;
	wcscpy_s(m_img_Text[12], L"../Image/Zerg_img/Scourge.png");;
	wcscpy_s(m_img_Text[13], L"../Image/Zerg_img/Devourer.png");
	wcscpy_s(m_img_Text[14], L"../Image/Protoss_img/scout.png");;
	wcscpy_s(m_img_Text[15], L"../Image/Protoss_img/Archon.png");;
	wcscpy_s(m_img_Text[16], L"../Image/Protoss_img/carrier.png");;
	wcscpy_s(m_img_Text[17], L"../Image/Protoss_img/mothership.png");;
	wcscpy_s(m_img_Text[18], L"../Image/Zerg_img/Guardian.png");;

	m_Scene_Begin = new CScene;
	m_Scene_End = new CScene;
	m_Scene_Stage1 = new CScene;
	m_Scene_stage2 = new CScene;
	m_Scene_stage3 = new CScene;
	m_Scene_StageClear = new CScene;

	m_Scene_End1 = new CScene;
	m_Scene_End2 = new CScene;
	m_Scene_End3 = new CScene;
	{
		images[0].Load(L"./Image/Item_img/Bullets.png");
		images[1].Load(L"./Image/Item_img/icon_ATKSPDUP.png");
		images[2].Load(TEXT("./Image/Item_img/icon_HPUP.png"));
		images[3].Load(TEXT("./Image/Item_img/icon_INVINCIBILITY.png"));
		images[4].Load(TEXT("./Image/Item_img/icon_PowUp.png"));

		// protoss
		images[5].Load(L"./Image/Terran_img/Wraith.png");
		images[6].Load(L"./Image/Terran_img/Valkyrie.png");
		images[7].Load(L"./Image/Terran_img/Battle Cruiser.png");
		images[8].Load(L"./Image/Terran_img/Dropship.png");
		images[9].Load(L"./Image/Terran_img/Vessel.png");
		images[10].Load(L"./Image/Zerg_img/Mutalisk.png");
		images[11].Load(L"./Image/Zerg_img/Queen.png");
		images[12].Load(L"./Image/Zerg_img/Scourge.png");
		images[13].Load(L"./Image/Zerg_img/Devourer.png");
		images[14].Load(L"./Image/Protoss_img/scout.png");
		images[15].Load(L"./Image/Protoss_img/Archon.png");
		images[16].Load(L"./Image/Protoss_img/carrier.png");
		images[17].Load(L"./Image/Protoss_img/mothership.png");
		images[18].Load(L"./Image/Zerg_img/Guardian.png");
	}

	//m_Player = new CPlayer;
	//m_Player->Init();

	// 플레이어 생성 메세지를 받아 생성하기 떄문에 nullptr로 초기화
	m_CurrentScene = SCENE_TYPE::ST_BEGIN;
    m_Scene_Begin->Init(L"./Image/Scene_Back_img/StartScene_Back.png", nullptr, nullptr, 0, true, 0);
	m_Scene_Stage1->Init(L"./Image/Scene_Back_img/Stage1_Back.png", nullptr, nullptr,3000, false, 1);
	m_Scene_Stage1->SetPreScene(m_Scene_Begin);
	m_Scene_stage2->Init(L"./Image/Scene_Back_img/Stage2_Back.png", nullptr, nullptr,3000, false, 2);
	m_Scene_stage2->SetPreScene(m_Scene_Stage1);
	m_Scene_stage3->Init(L"./Image/Scene_Back_img/Stage3_Back.png", nullptr, nullptr,3000, false, 3);
	m_Scene_stage3->SetPreScene(m_Scene_stage2);
	m_Scene_StageClear->Init(L"./Image/Scene_Back_img/Stage_Clear.png", nullptr, nullptr, 0, false, 0);
	m_Scene_StageClear->SetPreScene(m_Scene_stage3);
	m_Scene_End->Init(L"./Image/Scene_Back_img/End1.png", nullptr, nullptr, 0, false, 0);
	m_Scene_End->SetPreScene(m_Scene_stage3);

	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	switch (m_CurrentScene)
	{
	case SCENE_TYPE::ST_BEGIN:
		m_Scene_Begin->Input(fDeltaTime, nullptr);
		break;
	case SCENE_TYPE::ST_STAGE1:
		m_Scene_Stage1->Input(fDeltaTime, nullptr);
		break;
	case SCENE_TYPE::ST_STAGE2:
		m_Scene_stage2->Input(fDeltaTime, nullptr);
		break;
	case SCENE_TYPE::ST_STAGE3:
		m_Scene_stage3->Input(fDeltaTime, nullptr);
		break;
	case SCENE_TYPE::ST_CLEAR:
		m_Scene_StageClear->Input(fDeltaTime, nullptr);
		break;
	case SCENE_TYPE::ST_END:
		m_Scene_End->Input(fDeltaTime, nullptr);
		break;
	default:
		break;
	}
}

void CSceneManager::Update(float fDeltaTime)
{
	switch (m_CurrentScene)
	{
	case SCENE_TYPE::ST_BEGIN:
		m_Scene_Begin->Update(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE1:
		m_Scene_Stage1->Update(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE2:
		m_Scene_stage2->Update(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE3:
		m_Scene_stage3->Update(fDeltaTime);
		break;
	case SCENE_TYPE::ST_CLEAR:
		m_Scene_StageClear->Update(fDeltaTime);
		break;
	case SCENE_TYPE::ST_END:
		m_Scene_End->Update(fDeltaTime);
		break;
	default:
		break;
	}
}

void CSceneManager::LateUpdate(float fDeltaTime)
{
	switch (m_CurrentScene)
	{
	case SCENE_TYPE::ST_BEGIN:
		m_Scene_Begin->LateUpdate(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE1:
		m_Scene_Stage1->LateUpdate(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE2:
		m_Scene_stage2->LateUpdate(fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE3:
		m_Scene_stage3->LateUpdate(fDeltaTime);
		break;
	case SCENE_TYPE::ST_CLEAR:
		m_Scene_StageClear->LateUpdate(fDeltaTime);
		break;
	case SCENE_TYPE::ST_END:
		m_Scene_End->LateUpdate(fDeltaTime);
		break;
	default:
		break;
	}
}

void CSceneManager::Render(HDC mainhDC, HDC hDC, float fDeltaTime)
{
	switch (m_CurrentScene)
	{
	case SCENE_TYPE::ST_BEGIN:
		m_Scene_Begin->Render(mainhDC, hDC, fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE1:
		m_Scene_Stage1->Render(mainhDC, hDC, fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE2:
		m_Scene_stage2->Render(mainhDC, hDC, fDeltaTime);
		break;
	case SCENE_TYPE::ST_STAGE3:
		m_Scene_stage3->Render(mainhDC, hDC, fDeltaTime);
		break;
	case SCENE_TYPE::ST_CLEAR:
		m_Scene_StageClear->Render(mainhDC, hDC, fDeltaTime);
		break;
	case SCENE_TYPE::ST_END:
		m_Scene_End->Render(mainhDC, hDC, fDeltaTime);
		break;
	default:
		break;
	}
}


CPlayer* CSceneManager::GetPlayer()
{
	return m_MainPlayer;
}

bool CSceneManager::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_objectCreate:
	{
		int id = telegram.Sender;
		char* tmp = (char*)telegram.Extrainfo;
		OBJECT_TYPE* obj_type = new OBJECT_TYPE;
		memcpy(obj_type, tmp, sizeof(OBJECT_TYPE));

		POSITION* pos = new POSITION;
		memcpy(pos, (void*)(&tmp[sizeof(OBJECT_TYPE)]), sizeof(POSITION));
		
		CObject* pReceiver = CObjectManager::GetInst()->GetObjectFromID(telegram.Sender);

		if (pReceiver)
		{
			delete pos;
			delete obj_type;
			return true;
		}

		if (*obj_type == OBJECT_TYPE::OBJ_PLAYER) { // Player 생성
			m_MainPlayer = new CPlayer(id);
			m_MainPlayer->Init(1);
			m_MainPlayer->SetPos(*pos);

			// Player 생성 -> Scene마다 Player 셋팅
			m_Scene_Stage1->Set_MainPlayer(m_MainPlayer);
			m_Scene_stage2->Set_MainPlayer(m_MainPlayer);
			m_Scene_stage3->Set_MainPlayer(m_MainPlayer);
			return true;
		}
		
		if (*obj_type == OBJECT_TYPE::OBJ_ANOTHER_PLAYER) { // Player 생성
			m_AnotherPlayer = new CPlayer(id);
			m_AnotherPlayer->Init(3);
			m_AnotherPlayer->SetPos(*pos);

			// Player 생성 -> Scene마다 Player 셋팅
			m_Scene_Stage1->Set_AnotherPlayer(m_AnotherPlayer);
			m_Scene_stage2->Set_AnotherPlayer(m_AnotherPlayer);
			m_Scene_stage3->Set_AnotherPlayer(m_AnotherPlayer);
			return true;
		}

		if (m_Scene_Begin->GetEnable())
			return false;

		else if (m_Scene_Stage1->GetEnable())
			m_Scene_Stage1->AddObject(telegram.Sender, *obj_type, *pos);

		else if (m_Scene_stage2->GetEnable())
			m_Scene_stage2->AddObject(telegram.Sender, *obj_type, *pos);

		else if (m_Scene_stage3->GetEnable())
			m_Scene_stage3->AddObject(telegram.Sender, *obj_type, *pos);

		delete pos;
		delete obj_type;
	}
	break;
	case MESSAGE_TYPE::Msg_changeScene:
	{
		char* tmp = (char*)telegram.Extrainfo;
		int* scene_type = new int;
		memcpy(scene_type, tmp, sizeof(int));
		
		if ((int)m_CurrentScene == *scene_type)
		{
			delete scene_type;
			return true;
		}

		switch (*scene_type)
		{
		case (int)SCENE_TYPE::ST_BEGIN:
			m_CurrentScene = SCENE_TYPE::ST_BEGIN;
			m_Scene_Begin->SetEnable(true);
			delete scene_type;
			return true;
		case (int)SCENE_TYPE::ST_STAGE1:
			m_CurrentScene = SCENE_TYPE::ST_STAGE1;
			m_Scene_Stage1->SetEnable(true);
			delete scene_type;
			return true;
		case (int)SCENE_TYPE::ST_STAGE2:
			m_CurrentScene = SCENE_TYPE::ST_STAGE2;
			m_Scene_stage2->SetEnable(true);
			delete scene_type;
			return true;
		case (int)SCENE_TYPE::ST_STAGE3:
			m_CurrentScene = SCENE_TYPE::ST_STAGE3;
			m_Scene_stage3->SetEnable(true);
			delete scene_type;
			return true;
		case (int)SCENE_TYPE::ST_CLEAR:
			m_CurrentScene = SCENE_TYPE::ST_CLEAR;
			m_Scene_StageClear->SetEnable(true);
			delete scene_type;
			return true;
		case (int)SCENE_TYPE::ST_END:
			m_Scene_StageClear->SetEnable(false);
			delete scene_type;
			return true;
		}
	}
	default:
		break;
	}

	return false;
}
