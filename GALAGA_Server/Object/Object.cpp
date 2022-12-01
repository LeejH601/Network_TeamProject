#include "Object.h"
#include "../Scene/SceneManager.h"
#include "../Core.h"
#include "../Core/Timer.h"
#include "../Locator.h"
#include "../Network/NetworkDevice.h"

int CObject::m_iObjN = 0;

CObject::CObject()
{

}

CObject::CObject(const CObject& obj)
{
	*this = obj;

}

CObject::~CObject()
{
}

POSITION CObject::GetPos() const
{

	return m_tLTPos;
}

POSITION CObject::GetVector() const
{
	return m_tVector;
}

_SIZE CObject::GetSize() const
{
	return m_tSize;
}

bool CObject::GetLife() const
{
	return m_bLife;
}

float CObject::GetHP() const
{
	return m_fHP;
}

int CObject::GetID() const
{
	return m_iObjID;
}

void CObject::SetPos(const POSITION& tPos)
{
	m_tLTPos = tPos;

}

void CObject::SetVector(const POSITION& tVector)
{
	m_tVector = tVector;

}

void CObject::SetSize(const _SIZE tSize)
{
	m_tSize = tSize;

}

void CObject::SetLife(const bool bLife)
{
	m_bLife = bLife;

}

void CObject::SetHP(const float fHP)
{
	m_fHP = fHP;

}

void CObject::SetID(const int id)
{
	m_iObjID = id;
}



// init ( 이미지 파일 경로 , 화면에 출력할 오브젝트 위치 , 오브젝트 방향 , 오브젝트 사이즈 , 오브젝트 HP , png 파일에서의 사이즈 , png 파일에서의 위치 ) 
bool CObject::Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType)
{

	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	//m_img_Back.Load(imgText);
	//if (m_img_Back == NULL)
	//{
	//	m_img_Back = CSceneManager::GetInst()->GetCimage(imgText);
	//	if (m_img_Back)
	//		m_img_Back->SetTransparentColor(RGB(255, 255, 255));

	//}
	//if (wcscmp(imgText, L"../Bin/Zerg_img/Devourer.png") == 0 && obType == PLAYER_TYPE::PT_PLAYER)
	//{
	//	if (m_img_Back)
	//		m_img_Back->SetTransparentColor(RGB(0, 0, 0));
	//}




	//m_imgText = new WCHAR[lstrlen(imgText)];
	//StringCchCopyW(m_imgText, lstrlen(imgText), imgText);

	m_tLTPos = LTpos;
	m_tVector = Vector;
	m_tSize = Size;
	m_fHP = HP;
	m_bLife = true;


	//m_img_Size = imgSize;
	//m_img_LT = imgLT;



	return true;
}
void CObject::Update(float fDeltaTime)
{

}

void CObject::LateUpdate(float fDeltaTime)
{
}

bool CObject::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	RECT mypos = { m_tLTPos.x, m_tLTPos.y, m_tLTPos.x + m_tSize.x ,m_tLTPos.y + m_tSize.y };
	RECT CollisionPos = { ObjectLT.x + (ObjectSize.x / 4), ObjectLT.y , ObjectLT.x + ObjectSize.x - (ObjectSize.x / 4), ObjectLT.y + ObjectSize.y - (ObjectSize.y / 4) };
	RECT rcTemp;

	return IntersectRect(&rcTemp, &mypos, &CollisionPos);

}

void CObject::SendMessageToClient(Telegram& msg)
{
	if (CCore::GetInst()->m_hPlayer1)
	{
		CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second);
		EnterCriticalSection(&c_cs);
		CNetworkDevice* p;
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
		p->AddMessage(msg);
		LeaveCriticalSection(&c_cs);
	}

	if (CCore::GetInst()->m_hPlayer2)
	{
		CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer2, nullptr))->second);
		EnterCriticalSection(&c_cs);
		CNetworkDevice* p;
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);
		p->AddMessage(msg);
		LeaveCriticalSection(&c_cs);
	}
}

void CObject::SendMsgCreateObject(OBJECT_TYPE nType, POSITION pos)
{
	Telegram tel_CreateObject;
	tel_CreateObject.Sender = m_iObjID;
	tel_CreateObject.Receiver = 0;
	tel_CreateObject.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	tel_CreateObject.DispatchTime = CTimer::GetInst()->GetTime();
	char* extraInfo = new char[12];

	memcpy(&extraInfo[0], &nType, sizeof(OBJECT_TYPE));
	memcpy(&extraInfo[4], &pos, sizeof(POSITION));
	tel_CreateObject.Extrainfo = extraInfo;

	CObject::SendMessageToClient(tel_CreateObject);

}

void CObject::SendMsgMoveObject()
{
	Telegram tel_MoveObject;
	tel_MoveObject.Sender = m_iObjID;
	tel_MoveObject.Receiver = m_iObjID;
	tel_MoveObject.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
	tel_MoveObject.DispatchTime = CTimer::GetInst()->GetTime();
	tel_MoveObject.Extrainfo = new char[8];
	memcpy(tel_MoveObject.Extrainfo, &m_tLTPos, sizeof(POSITION));

	CObject::SendMessageToClient(tel_MoveObject);

}

bool CObject::HandleMessage(const Telegram& telegram)
{
	return false;
}
//=================================================================================================

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	return true;
}

void CObjectManager::RegisterObject(CObject* NewObject)
{
	ObjectSet.insert(NewObject);
}

CObject* CObjectManager::GetObjectFromID(int id)
{
	CObject dummyObject;
	dummyObject.SetID(id);
	auto it = ObjectSet.find(&dummyObject);

	if (it != ObjectSet.end())
		return *it;

	return nullptr;
}

void CObjectManager::RemoveObject(CObject* pObject)
{
	ObjectSet.erase(pObject);
}

void CObjectManager::RemoveObject(int id)
{
	CObject dummyObject;
	dummyObject.SetID(id);
	ObjectSet.erase(&dummyObject);
}