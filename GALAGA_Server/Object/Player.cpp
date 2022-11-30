#include	"Player.h"
#include "../Core/Timer.h"
#include "../Network/NetworkDevice.h"
#include "../Object/BulletList.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	CObject::~CObject();

	if (m_myBulletList)
		m_myBulletList->EraseAll();

}

int CPlayer::Init()
{

	m_myBulletList = new CBulletList;

	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	m_bDie = false;
	m_fSpeed = 300.0f;

	return m_iObjID;
}
void CPlayer::Update(float fDeltaTime)
{
	if (m_myBulletList)
		m_myBulletList->Update(fDeltaTime);
}
void CPlayer::SendCreateMessage(CNetworkDevice* pNetworkDevice, OBJECT_TYPE obj_type)
{
	Telegram tel_CreateObject;
	tel_CreateObject.Sender = m_iObjID;
	tel_CreateObject.Receiver = 0;
	tel_CreateObject.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	tel_CreateObject.DispatchTime = CTimer::GetInst()->GetTime();
	char* extraInfo = new char[12];

	int nType = (int)obj_type;

	memcpy(&extraInfo[0], &nType, sizeof(OBJECT_TYPE));
	memcpy(&extraInfo[4], &m_tLTPos, sizeof(POSITION));
	tel_CreateObject.Extrainfo = extraInfo;

	pNetworkDevice->AddMessage(tel_CreateObject);

	delete[] tel_CreateObject.Extrainfo;
}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectCreate:// extrainfo: ObjectType, Position
	{
		
		int ObjectType;
		POSITION Position;
		POSITION BulletSize = { 18,30 };
		memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
		memcpy(&Position, (char*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
		if (ObjectType == (int)OBJECT_TYPE::PLAYER_BULLET) // Bullet »ý¼º
		{
			m_myBulletList->AddBullet(Position, BulletSize, 800.0f);
		}
		return true;
	}
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position (4byte + 12byte)
	{
		int ObjectType;
		POSITION Position;
		memcpy(&ObjectType, msg.Extrainfo, sizeof(int));
		memcpy(&Position, (char*)msg.Extrainfo + sizeof(int), sizeof(POSITION));
		return true;
	}
	case MESSAGE_TYPE::Msg_objectChangeState: //extrainfo: ObjectState
	{
		int ObjectState;
		memcpy(&ObjectState, msg.Extrainfo, sizeof(int));
		return true;
	}
	default:
		break;
	}

	return false;

}
