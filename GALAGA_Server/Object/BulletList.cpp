#include	"BulletList.h"
#include	"Bullet.h"
CBulletList::CBulletList()
{

}

CBulletList::~CBulletList()
{

	EraseAll();
}

void CBulletList::AddBullet(POSITION playerLT, POSITION playerSize, float Speed)
{
	POSITION BulletSize = { 18,30 };
	POSITION BulletLTPos = { playerLT.x + playerSize.x / 2 - BulletSize.x / 2, playerLT.y - BulletSize.y };

	CBullet* pBullet = new CBullet();
	pBullet->Init(BulletLTPos, BulletSize, 800.0f);
	m_listBulletList.push_back(pBullet);

}

// BulletSize에 왜 MonsterSize를 넣어주지?
void CBulletList::AddBullet(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed)
{
	POSITION BulletSize = { MonsterSize.x, MonsterSize.y };
	POSITION BulletLTPos = { MonsterLT.x + MonsterSize.x / 2 - BulletSize.x / 2, MonsterLT.y - BulletSize.y };

	CBullet* pBullet = new CBullet();
	pBullet->Init(BulletLTPos, BulletSize, BulletVector, Speed);
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

	for (std::list<class CBullet*>::iterator it = m_listBulletList.begin(); it != m_listBulletList.end(); it++)
	{
		if (*it)
			(*it)->Update(fDeltaTime);
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
		if (!((*it)->GetEnbale()))
		{
			CBullet* pBullet = *it;
			it = m_listBulletList.erase(it);
			SAFE_DELETE(pBullet);
			if (it != m_listBulletList.begin())
				it--;
			else if (it == m_listBulletList.end()) {
				break;
			}
		}
	}
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
