#include "Player.h"
#include "../Core.h"
#include "../Locator.h"
#include "../Core/Timer.h"
#include "../Network/NetworkDevice.h"

CPlayer::CPlayer()
{
}

int CPlayer::Init()
{
	m_iObjID = m_iObjN++;
	CObjectManager::GetInst()->RegisterObject(this);

	m_bDie = false;
	m_fSpeed = 300.0f;

	return m_iObjID;
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

void CPlayer::SendMoveMessage(CNetworkDevice* pNetworkDevice)
{
	Telegram tel_MoveObject;
	tel_MoveObject.Sender = m_iObjID;
	tel_MoveObject.Receiver = m_iObjID;
	tel_MoveObject.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
	tel_MoveObject.DispatchTime = CTimer::GetInst()->GetTime();
	tel_MoveObject.Extrainfo = new char[8];
	memcpy(tel_MoveObject.Extrainfo, &m_tLTPos, sizeof(POSITION));

	pNetworkDevice->AddMessage(tel_MoveObject);

	delete[] tel_MoveObject.Extrainfo;
}

bool CPlayer::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove:
	{
		POSITION* pos = new POSITION;
		memcpy(pos, msg.Extrainfo, sizeof(POSITION));

		SetPos(*pos);

		delete pos;

		switch (m_iObjID)
		{
		case 1:
			if (CCore::GetInst()->m_hPlayer2)
			{
				CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer2, nullptr))->second);
				EnterCriticalSection(&c_cs);
				CNetworkDevice* p;
				p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);
				SendMoveMessage(p);
				LeaveCriticalSection(&c_cs);
			}
			break;
		case 2:
			if(CCore::GetInst()->m_hPlayer1)
			{
				CRITICAL_SECTION& c_cs = const_cast<CRITICAL_SECTION&>(client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second);
				EnterCriticalSection(&c_cs);
				CNetworkDevice* p;
				p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
				SendMoveMessage(p);
				LeaveCriticalSection(&c_cs);
			}
			break;
		default:

			break;
		}


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
