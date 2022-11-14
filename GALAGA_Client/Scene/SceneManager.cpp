#include "../Sound/SoundManager.h"
#include "SceneManager.h"
#include "Scene.h"

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

	SAFE_DELETE(m_Player);



}

bool CSceneManager::Init()
{
	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	wcscpy_s(m_img_Text[0], L"../Bin/Item_img/Bullets.png");

	wcscpy_s(m_img_Text[1], L"../Bin/Item_img/icon_ATKSPDUP.png");
	wcscpy_s(m_img_Text[2], L"../Bin/Item_img/icon_HPUP.png");
	wcscpy_s(m_img_Text[3], L"../Bin/Item_img/invincibility (2).png");
	wcscpy_s(m_img_Text[4], L"../Bin/Item_img/icon_PowUp.png");;

	wcscpy_s(m_img_Text[5], L"../Bin/Terran_img/Wraith.png");;
	wcscpy_s(m_img_Text[6], L"../Bin/Terran_img/Valkyrie.png");;
	wcscpy_s(m_img_Text[7], L"../Bin/Terran_img/Battle Cruiser.png");;
	wcscpy_s(m_img_Text[8], L"../Bin/Terran_img/Dropship.png");;
	wcscpy_s(m_img_Text[9], L"../Bin/Terran_img/Vessel.png");;
	wcscpy_s(m_img_Text[10], L"../Bin/Zerg_img/Mutalisk.png");;
	wcscpy_s(m_img_Text[11], L"../Bin/Zerg_img/Queen.png");;
	wcscpy_s(m_img_Text[12], L"../Bin/Zerg_img/Scourge.png");;
	wcscpy_s(m_img_Text[13], L"../Bin/Zerg_img/Devourer.png");
	wcscpy_s(m_img_Text[14], L"../Bin/Protoss_img/scout.png");;
	wcscpy_s(m_img_Text[15], L"../Bin/Protoss_img/Archon.png");;
	wcscpy_s(m_img_Text[16], L"../Bin/Protoss_img/carrier.png");;
	wcscpy_s(m_img_Text[17], L"../Bin/Protoss_img/mothership.png");;
	wcscpy_s(m_img_Text[18], L"../Bin/Zerg_img/Guardian.png");;





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
		// 아이템 
		images[0].Load(L"../Bin/Item_img/Bullets.png");
		images[1].Load(L"../Bin/Item_img/icon_ATKSPDUP.png");
		images[2].Load(TEXT("../Bin/Item_img/icon_HPUP.png"));
		images[3].Load(TEXT("../Bin/Item_img/invincibility (2).png"));
		images[4].Load(TEXT("../Bin/Item_img/icon_PowUp.png"));


		// protoss
		images[5].Load(L"../Bin/Terran_img/Wraith.png");
		images[6].Load(L"../Bin/Terran_img/Valkyrie.png");
		images[7].Load(L"../Bin/Terran_img/Battle Cruiser.png");
		images[8].Load(L"../Bin/Terran_img/Dropship.png");
		images[9].Load(L"../Bin/Terran_img/Vessel.png");
		images[10].Load(L"../Bin/Zerg_img/Mutalisk.png");
		images[11].Load(L"../Bin/Zerg_img/Queen.png");
		images[12].Load(L"../Bin/Zerg_img/Scourge.png");
		images[13].Load(L"../Bin/Zerg_img/Devourer.png");
		images[14].Load(L"../Bin/Protoss_img/scout.png");
		images[15].Load(L"../Bin/Protoss_img/Archon.png");
		images[16].Load(L"../Bin/Protoss_img/carrier.png");
		images[17].Load(L"../Bin/Protoss_img/mothership.png");
		images[18].Load(L"../Bin/Zerg_img/Guardian.png");




	}

	// Player 파일 존재X
	//m_Player = new CPlayer;
	//m_Player->Init();


	// 각 Scene 에 해당하는 png 이미지들을 로드합니다...
	m_Scene_Begin->Init(L"./Scene_Back_img/StartScene_Back.png", nullptr, 0, true, 0);
	m_Scene_Stage1->Init(L"./Scene_Back_img/Stage1_Back.png", m_Player, 8000, false, 1);
	m_Scene_stage2->Init(L"./Scene_Back_img/Stage2_Back.png", m_Player, 8000, false, 2);
	m_Scene_stage3->Init(L"./Scene_Back_img/Stage3_Back.png", m_Player, 8000, false, 3);
	m_Scene_StageClear->Init(L"./Scene_Back_img/Stage_Clear.png", nullptr, 0, false, 0);

	m_Scene_End->Init(L"./Scene_Back_img/End1.png", nullptr, 0, false, 0);




	//m_Scene_End->Init(m_Player,false);
	//m_Scene_stage3->Init(m_Player,false);


	return true;
}

void CSceneManager::Input(float fDeltaTime)
{

	// Scene  의 enable 이 true 인 것만 구동합니다...
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Input(fDeltaTime, m_Scene_Stage1);

	else if (m_Scene_Stage1->GetEnable())
		m_Scene_Stage1->Input(fDeltaTime, m_Scene_stage2);

	else if (m_Scene_stage2->GetEnable())
		m_Scene_stage2->Input(fDeltaTime, nullptr);

	else if (m_Scene_stage3->GetEnable())
		m_Scene_stage3->Input(fDeltaTime, nullptr);

	else if (m_Scene_End->GetEnable())
		m_Scene_End->Input(fDeltaTime, nullptr);

	// Player 파일 존재X
	// 시작 화면 - > stage 1 장면 전환
	//if (m_Player->GetMyType() != OBJECT_TYPE::OT_NONE)
	//{
	//	if (GetAsyncKeyState(VK_SPACE))
	//	{
	//		if (m_Scene_Begin->GetEnable() == true)
	//		{
	//			m_Scene_Begin->SetEnable(false);
	//			m_Scene_Stage1->SetEnable(true);
	//			CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 1);

	//		}
	//		else if (m_Scene_End->GetEnable() == true)
	//		{
	//			m_Scene_End->SetEnable(false);
	//			CCore::GetInst()->SetEnd();


	//		}

	//	}

	//}

	//if (m_Player->GetMyType() == OBJECT_TYPE::OT_NONE)
	//{
	//	if (GetAsyncKeyState('1') & 0x8000)
	//	{
	//		m_Player->SetType(1);
	//		m_Player->Init();


	//	}
	//	if (GetAsyncKeyState('2') & 0x8000)
	//	{
	//		m_Player->SetType(2);
	//		m_Player->Init();

	//	}
	//	if (GetAsyncKeyState('3') & 0x8000)
	//	{
	//		m_Player->SetType(3);
	//		m_Player->Init();

	//	}


	//}


}

void CSceneManager::Update(float fDeltaTime)
{
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Update(fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
	{
		// 해당 씬이 종료됨 == 1 
		if (m_Scene_Stage1->Update(fDeltaTime) == 1)
		{
			m_Scene_Stage1->SetEnable(false);
			// 다음씬이 진행되도록 합니다...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
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
				CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 2);
				break;
			case 3:
				m_Scene_StageClear->SetEnable(false);
				m_Scene_stage3->SetEnable(true);
				CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 3);
				break;
			case 0:
				m_Scene_StageClear->SetEnable(false);
				m_Scene_End->SetEnable(true);
				CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 0);


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
			// 다음씬이 진행되도록 합니다...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
			NextStageNum = 3;


		}
	}

	else if (m_Scene_stage3->GetEnable())
	{
		if (m_Scene_stage3->Update(fDeltaTime) == 1)
		{
			m_Scene_stage3->SetEnable(false);
			// 다음씬이 진행되도록 합니다...
			m_Scene_StageClear->SetEnable(true);
			//m_Scene_stage2->SetEnable(true);
			CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_TERRAN, 4);
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

void CSceneManager::Render(HDC mainhDC, HDC hDC, float fDeltaTime)
{
	if (m_Scene_Begin->GetEnable())
		m_Scene_Begin->Render(mainhDC, hDC, fDeltaTime);

	else if (m_Scene_StageClear->GetEnable())
		m_Scene_StageClear->Render(mainhDC, hDC, fDeltaTime);

	else if (m_Scene_Stage1->GetEnable())
		m_Scene_Stage1->Render(mainhDC, hDC, fDeltaTime);

	else if (m_Scene_stage2->GetEnable())
		m_Scene_stage2->Render(mainhDC, hDC, fDeltaTime);

	else if (m_Scene_stage3->GetEnable())
		m_Scene_stage3->Render(mainhDC, hDC, fDeltaTime);

	else if (m_Scene_End->GetEnable())
		m_Scene_End->Render(mainhDC, hDC, fDeltaTime);




}

CPlayer* CSceneManager::GetPlayer()
{
	return m_Player;
}

bool CSceneManager::HandleMessage(const Telegram& telegram)
{
	if (telegram.Msg != (int)MESSAGE_TYPE::Msg_changeScene)
		return false;

	switch ((int)(&telegram.Extrainfo))
	{
	case (int)SCENE_TYPE::ST_BEGIN:
		m_Scene_Begin->SetEnable(true);
		m_Scene_Stage1->SetEnable(false);
		m_Scene_stage2->SetEnable(false);
		m_Scene_stage3->SetEnable(false);
		m_Scene_StageClear->SetEnable(false);
		m_Scene_End->SetEnable(false);
		break;
	case (int)SCENE_TYPE::ST_STAGE1:
		m_Scene_Begin->SetEnable(false);
		m_Scene_Stage1->SetEnable(true);
		m_Scene_stage2->SetEnable(false);
		m_Scene_stage3->SetEnable(false);
		m_Scene_StageClear->SetEnable(false);
		m_Scene_End->SetEnable(false);
		break;
	case (int)SCENE_TYPE::ST_STAGE2:
		m_Scene_Begin->SetEnable(false);
		m_Scene_Stage1->SetEnable(false);
		m_Scene_stage2->SetEnable(true);
		m_Scene_stage3->SetEnable(false);
		m_Scene_StageClear->SetEnable(false);
		m_Scene_End->SetEnable(false);
		break;
	case (int)SCENE_TYPE::ST_STAGE3:
		m_Scene_Begin->SetEnable(false);
		m_Scene_Stage1->SetEnable(false);
		m_Scene_stage2->SetEnable(false);
		m_Scene_stage3->SetEnable(true);
		m_Scene_StageClear->SetEnable(false);
		m_Scene_End->SetEnable(false);
		break;
	case (int)SCENE_TYPE::ST_CLEAR:
		m_Scene_Begin->SetEnable(false);
		m_Scene_Stage1->SetEnable(false);
		m_Scene_stage2->SetEnable(false);
		m_Scene_stage3->SetEnable(false);
		m_Scene_StageClear->SetEnable(true);
		m_Scene_End->SetEnable(false);
		break;
	case (int)SCENE_TYPE::ST_END:
		m_Scene_Begin->SetEnable(false);
		m_Scene_Stage1->SetEnable(false);
		m_Scene_stage2->SetEnable(false);
		m_Scene_stage3->SetEnable(false);
		m_Scene_StageClear->SetEnable(false);
		m_Scene_End->SetEnable(true);
		break;
	}
}
