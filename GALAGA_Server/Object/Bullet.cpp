#include "Bullet.h"
#include "../Network/NetworkDevice.h"
#include "../Core.h"
#include "../Locator.h"


CBullet::CBullet()
{

}

CBullet::~CBullet()
{

}

					    //BULLET_TYPE   POSITION    OBJECT_ENUM
void CBullet::Msg_Create(OBJECT_TYPE TYPE, POSITION POS)
{
	Telegram telegram;
	telegram.Sender = m_iObjID;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	telegram.Extrainfo = new char[sizeof(int) + sizeof(POSITION)];
	memcpy(telegram.Extrainfo, &TYPE, sizeof(int)); // Bullet_Type
	memcpy((char*)telegram.Extrainfo + sizeof(int), & POS, sizeof(POSITION)); // Position

	CObject::SendMessageToClient(telegram);

}

void CBullet::Msg_Move(POSITION POS, int ObjectEnum)
{
	Telegram telegram;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
	telegram.Extrainfo = new char[sizeof(POSITION) + sizeof(int)];
	memcpy(&telegram.Extrainfo, &POS, sizeof(POSITION));
	memcpy((char*)telegram.Extrainfo + sizeof(int), &ObjectEnum, sizeof(int));
	auto cs = client_cs.find(CS_PAIR(CCore::GetInst()->m_hPlayer1, nullptr))->second;
	EnterCriticalSection(&cs);
	CNetworkDevice* p;
	if (!CCore::GetInst()->m_hPlayer2)
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer1);
	else
		p = Locator.GetNetworkDevice(CCore::GetInst()->m_hPlayer2);

	p->AddMessage(telegram);
	LeaveCriticalSection(&cs);
}



bool CBullet::HandleMessage(const Telegram& msg)
{
	switch ((MESSAGE_TYPE)msg.Msg)
	{
	case MESSAGE_TYPE::Msg_objectMove: //extrainfo: ObjectType, Position 
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
		return true;
	}

	return false;
}


bool CBullet::Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed)
{
	// 이미지 파일 크기 값 변수로 바꾸기
	CObject::Init(PlayerLT, POSITION(0, -1), PlayerSize, 1000.0f, PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	CObject::Init(MonsterLT, BulletVector, MonsterSize, 1000.0f, PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 1000.0f;
	m_Range = 0.0f;

	return true;
}

void CBullet::Update(float fDeltaTime)
{

	CObject::SetPos(CObject::GetPos() + ((CObject::GetVector() * fDeltaTime) * m_fSpeed));

	m_Range += fDeltaTime * m_fSpeed;

	if (m_Range >= m_MaxRange)
		SetEnalbeFalse();

	CObject::SendMsgMoveObject();

}

bool CBullet::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);
}

