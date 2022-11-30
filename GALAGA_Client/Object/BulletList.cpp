#include	"BulletList.h"
#include	"Bullet.h"
#include	"../Core/Timer.h"
#include	"../Network/NetworkDevice.h"
CBulletList::CBulletList()
{

}

CBulletList::CBulletList(int id)
{
	ObjectId = id;
}

CBulletList::~CBulletList()
{

	EraseAll();
}

void CBulletList::AddBullet(int id,  POSITION playerLT, POSITION playerSize, float Speed)
{
	POSITION BulletSize = { 18,30 };
	POSITION BulletLTPos = { playerLT.x + playerSize.x / 2 - BulletSize.x / 2, playerLT.y - BulletSize.y };

	CBullet* pBullet = new CBullet();
	pBullet->Init(BulletLTPos, BulletSize, 800.0f);
	pBullet->RegisterObject(id);

	m_listBulletList.push_back(pBullet);
}

void CBulletList::AddBullet(int id, POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	POSITION BulletSize = { MonsterSize.x, MonsterSize.y };
	POSITION BulletLTPos = { MonsterLT.x + MonsterSize.x / 2 - BulletSize.x / 2, MonsterLT.y - BulletSize.y };

	CBullet* pBullet = new CBullet();
	pBullet->Init(BulletLTPos, BulletSize, BulletVector, Speed);
	pBullet->RegisterObject(id);

	m_listBulletList.push_back(pBullet);
}

int CBulletList::Collision(float fDeltatime, POSITION ObjectLT, _SIZE ObjectSize)
{
	int CollisionN = 0; // 충돌 횟수

	for (CBullet* pBullet : m_listBulletList) {
		if (pBullet->Collision(fDeltatime, ObjectLT, ObjectSize)) {
			CollisionN++;
			Erase(pBullet);
		}
	}
	return CollisionN;
}

void CBulletList::Update(float fDeltaTime)
{
	// BulletList의 원소인 모든 Bullet 거리 이동
	for (CBullet* pBullet : m_listBulletList) {
		if (pBullet)
			pBullet->Update(fDeltaTime);
	}

}


void CBulletList::Update(float fDeltaTime, _SIZE _size)
{
	for (CBullet* pBullet : m_listBulletList) {
		if (pBullet)
		{
			pBullet->SetSize(pBullet->GetSize() + _size);
			pBullet->SetPos(pBullet->GetPos() - (_size / 2));
			pBullet->Update(fDeltaTime);
		}
	}
}

void CBulletList::LateUpdate(float fDeltaTime)
{
	for (std::list<class CBullet*>::iterator it = m_listBulletList.begin(); it != m_listBulletList.end(); it++)
	{
		/*if (!((*it)->GetEnbale()))
		{
			CBullet* pBullet = *it;
			it = m_listBulletList.erase(it);
			SAFE_DELETE(pBullet);
		}*/
	}
}

void CBulletList::RenderAll(HDC mainDC, HDC hdc, float fDeltaTime)
{
	for (CBullet* p : m_listBulletList)
		p->Render(mainDC, hdc, fDeltaTime);
}


void CBulletList::Erase(CBullet* delNode)
{
	if (delNode == nullptr)
		return;
	
	m_listBulletList.remove(delNode);
	SAFE_DELETE(delNode);
}

bool CBulletList::EraseAll()
{
	for (CBullet* p : m_listBulletList)
		SAFE_DELETE(p);
	m_listBulletList.clear();

	return true;
}

void CBulletList::Set_Object(int id)
{
	ObjectId = id;
}
