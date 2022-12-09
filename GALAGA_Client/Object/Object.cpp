#include "Object.h"
#include "../Core/Timer.h"
#include "../Scene/SceneManager.h"

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
	//m_img_Back.Destroy();

	if (m_imgText != nullptr) {
		delete[] m_imgText;
		m_imgText = nullptr;
	}

}

void CObject::Changeimg(const WCHAR* imgText, POSITION imgSize, POSITION imgLT)
{
	/*if (m_img_Back)
		m_img_Back.Destroy();


	m_img_Back.Load(imgText);*/

	m_img_Back = CSceneManager::GetInst()->GetCimage(imgText);
	m_img_Back->SetTransparentColor(RGB(255, 255, 255));


	if (m_imgText)
		delete[]m_imgText;

	m_imgText = new WCHAR[lstrlen(imgText)];
	StringCchCopyW(m_imgText, lstrlen(imgText), imgText);

	m_img_Size = imgSize;
	m_img_LT = imgLT;


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



// init ( �̹��� ���� ��� , ȭ�鿡 ����� ������Ʈ ��ġ , ������Ʈ ���� , ������Ʈ ������ , ������Ʈ HP , png ���Ͽ����� ������ , png ���Ͽ����� ��ġ ) 
bool CObject::Init(const WCHAR* imgText, POSITION LTpos, POSITION Vector, _SIZE Size, float HP, POSITION imgSize, POSITION imgLT, PLAYER_TYPE obType)
{

	/*m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);*/

	//m_img_Back.Load(imgText);
	if (m_img_Back == NULL)
	{
		m_img_Back = CSceneManager::GetInst()->GetCimage(imgText);
		if (m_img_Back)
			m_img_Back->SetTransparentColor(RGB(255, 255, 255));

	}
	if (wcscmp(imgText, L"../Image/Zerg_img/Devourer.png") == 0 && obType == PLAYER_TYPE::PT_PLAYER)
	{
		if (m_img_Back)
			m_img_Back->SetTransparentColor(RGB(0, 0, 0));
	}




	m_imgText = new WCHAR[lstrlen(imgText)];
	StringCchCopyW(m_imgText, lstrlen(imgText), imgText);

	m_tLTPos = LTpos;
	m_tVector = Vector;
	m_tSize = Size;
	m_fHP = HP;
	m_bLife = true;


	m_img_Size = imgSize;
	m_img_LT = imgLT;



	return true;
}

void CObject::Input(float fDeltaTime)
{
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

void CObject::Render(HDC mainhDC, HDC hdc, float fDeltaTime)
{

	if (m_img_Back)
	{
		m_img_Back->Draw(hdc, m_tLTPos.x, m_tLTPos.y, m_tSize.x, m_tSize.y,
			m_img_LT.x, m_img_LT.y, m_img_Size.x, m_img_Size.y);

	}

}
void CObject::RegisterObject(const int id)
{
	SetID(id);
	CObjectManager::GetInst()->RegisterObject(this);
}
bool CObject::HandleMessage(const Telegram& telegram)
{
	switch (static_cast<MESSAGE_TYPE>(telegram.Msg))
	{
	case MESSAGE_TYPE::Msg_objectMove:
	{
		POSITION* pos = new POSITION;
		memcpy(pos, telegram.Extrainfo, sizeof(POSITION));

		SetPos(*pos);
		delete pos;
	}
	return true;
	case MESSAGE_TYPE::Msg_objectChangeState:
	{	OBJECT_STATE* state = new OBJECT_STATE;
		memcpy(state, telegram.Extrainfo, sizeof(OBJECT_STATE));

		if (m_eObjState == *state)
		{
			delete state;
			return true;
		}

		switch (*state)
		{
		case OBJECT_STATE::DESTORY:
			m_eObjState = OBJECT_STATE::DESTORY;
			m_bEnable = false;
			break;
		case OBJECT_STATE::ERASE:
			m_eObjState = OBJECT_STATE::ERASE;
			break;
		}
		delete state;
		return true;
	}
	default:
		break;
	}
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