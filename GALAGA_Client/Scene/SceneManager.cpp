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

	SAFE_DELETE(m_Player);
}

bool CSceneManager::Init()
{

	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);


	wcscpy_s(m_img_Text[0], L"../Image/Item_img/Bullets.png");
	wcscpy_s(m_img_Text[1], L"../Image/Item_img/icon_ATKSPDUP.png");
	wcscpy_s(m_img_Text[2], L"../Image/Item_img/icon_HPUP.png");
	wcscpy_s(m_img_Text[3], L"../Image/Item_img/invincibility (2).png");
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
		images[3].Load(TEXT("./Image/Item_img/invincibility (2).png"));
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

	m_Player = new CPlayer;
	//m_Player->Init();

	m_Scene_Begin->Init(L"./Image/Scene_Back_img/StartScene_Back.png", nullptr, 0, true, 0);
	m_Scene_Stage1->Init(L"./Image/Scene_Back_img/Stage1_Back.png", m_Player, 3000, false, 1);
	m_Scene_stage2->Init(L"./Image/Scene_Back_img/Stage2_Back.png", m_Player, 3000, false, 2);
	m_Scene_stage3->Init(L"./Image/Scene_Back_img/Stage3_Back.png", m_Player, 3000, false, 3);
	m_Scene_StageClear->Init(L"./Image/Scene_Back_img/Stage_Clear.png", nullptr, 0, false, 0);
	m_Scene_End->Init(L"./Image/Scene_Back_img/End1.png", nullptr, 0, false, 0);

	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
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

	//��� ��ȯ
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
		// �� ����
		if (m_Scene_Stage1->Update(fDeltaTime) == 1)
		{
			CSoundManager::GetInst()->playSound(TRIBE_TYPE::OT_TERRAN, 4);
		}

	}
	else if (m_Scene_StageClear->GetEnable())
	{
		
	}
	else if (m_Scene_stage2->GetEnable())
	{
		if (m_Scene_stage2->Update(fDeltaTime) == 1)
		{
			CSoundManager::GetInst()->playSound(TRIBE_TYPE::OT_TERRAN, 4);
		}
	}
	else if (m_Scene_stage3->GetEnable())
	{
		if (m_Scene_stage3->Update(fDeltaTime) == 1)
		{
			CSoundManager::GetInst()->playSound(TRIBE_TYPE::OT_TERRAN, 4);
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

		//	int Object_Type; // 해당 오브젝트의 enum
		//	POSITION Position;
		//	int Object_Type2; // 오브젝트 enum -> 어떤 오브젝트인지
		//	memcpy(&Object_Type, telegram.Extrainfo, sizeof(int));
		//	memcpy(&Position, (void*)((char*)telegram.Extrainfo + sizeof(int)), sizeof(POSITION));
		//	memcpy(&Object_Type2, (void*)((char*)telegram.Extrainfo + sizeof(int) + sizeof(POSITION)), sizeof(int));

		//	switch (Object_Type2)
		//	{
		//	case 0: // Monster
		//		if (m_Scene_Begin->GetEnable())
		//			return false;
		//		else if (m_Scene_Stage1->GetEnable())
		//			m_Scene_Stage1->AddMonster((Monster_type)Object_Type, Position);

		//		else if (m_Scene_stage2->GetEnable())
		//			m_Scene_stage2->AddMonster((Monster_type)Object_Type, Position);

		//		else if (m_Scene_stage3->GetEnable())
		//			m_Scene_stage3->AddMonster((Monster_type)Object_Type, Position);
		//		return true;

		//	case 1: // Bullet
		//				//POSITION Position;
		//		if (m_Scene_Begin->GetEnable())
		//			return false;
		//		else if (m_Scene_Stage1->GetEnable())
		//			m_Scene_Stage1->AddMonsterBullet(Object_Type, Position);
		//		else if (m_Scene_stage2->GetEnable())
		//			m_Scene_stage2->AddMonsterBullet(Object_Type, Position);
		//		else if (m_Scene_stage3->GetEnable())
		//			m_Scene_stage3->AddMonsterBullet(Object_Type, Position);
		//		return true;
		//	}
		//}
	}
	break;
	case MESSAGE_TYPE::Msg_changeScene:
		switch (*((int*)telegram.Extrainfo))
		{
		case (int)SCENE_TYPE::ST_BEGIN:
			m_Scene_Begin->SetEnable(true);
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(false);
			m_Scene_End->SetEnable(false);
			return true;
		case (int)SCENE_TYPE::ST_STAGE1:
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(true);
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(false);
			m_Scene_End->SetEnable(false);
			return true;
		case (int)SCENE_TYPE::ST_STAGE2:
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(true);
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(false);
			m_Scene_End->SetEnable(false);
			return true;
		case (int)SCENE_TYPE::ST_STAGE3:
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(true);
			m_Scene_StageClear->SetEnable(false);
			m_Scene_End->SetEnable(false);
			return true;
		case (int)SCENE_TYPE::ST_CLEAR:
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(true);
			m_Scene_End->SetEnable(false);
			return true;
		case (int)SCENE_TYPE::ST_END:
			m_Scene_Begin->SetEnable(false);
			m_Scene_Stage1->SetEnable(false);
			m_Scene_stage2->SetEnable(false);
			m_Scene_stage3->SetEnable(false);
			m_Scene_StageClear->SetEnable(false);
			m_Scene_End->SetEnable(true);
			return true;
			break;
		}
	default:
		break;
	}

	return false;
}
