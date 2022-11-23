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
void CBullet::Msg_Create(int TYPE, POSITION POS)
{
	int ObjectEnum = 1;
	Telegram telegram;
	telegram.Receiver = 0;
	telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
	telegram.Extrainfo = new char[sizeof(int) + sizeof(POSITION) + sizeof(int)];
	memcpy(telegram.Extrainfo, &TYPE, sizeof(int)); // Bullet_Type
	memcpy((char*)telegram.Extrainfo + sizeof(int), & POS, sizeof(POSITION)); // Position
	memcpy((char*)telegram.Extrainfo + sizeof(int) + sizeof(POSITION), &ObjectEnum, sizeof(int));
	//memcpy((char*)telegram.Extrainfo + sizeof(int) + sizeof(int), &ObjectEnum, sizeof(int));
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
	// �̹��� ���� ũ�� �� ������ �ٲٱ�
	CObject::Init(L"../Image/Item_img/Bullets.png", PlayerLT, POSITION(0, 1),
		PlayerSize, 1000.0f, POSITION(8, 15), POSITION(84, 42), PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 700.0f;
	m_Range = 0.0f;

	return true;
}

bool CBullet::Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	CObject::Init(L"../Image/Item_img/Bullets.png", MonsterLT, BulletVector,
		MonsterSize, 1000.0f, POSITION(16, 16), POSITION(167, 297), PLAYER_TYPE::PT_MONSTER);

	m_fSpeed = Speed;
	m_bEnable = true;
	m_MaxRange = 1000.0f;
	m_Range = 0.0f;

	return true;
}

bool CBullet::Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize)
{
	return CObject::Collision(fDeltaTime, ObjectLT, ObjectSize);
}