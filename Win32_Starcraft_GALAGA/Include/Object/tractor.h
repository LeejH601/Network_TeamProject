#pragma once
#include "Monster.h"

class CTractor : public CMonster
{
	// CSceneManager 에서 CPlayer의 private 으로 설정된 기본 생성자에 접근하기 위해서 선언 되었습니다...
	friend class CSceneManager;
public:

	CTractor();
	CTractor(const CTractor& player);
	virtual ~CTractor();

private:
	CBulletList* m_bulletList;
	float LastFireTime = NULL;
	float LastUpdateTime = NULL;
	_SIZE DetBulletSize = { 0.5f,0 };


public:
	class CBulletList* GetMyBulletList()
	{

		if (this == nullptr)
			int i = 0;

		if (m_bulletList)
			return m_bulletList;
		else
			return nullptr;
	}
	void RenderExplode(HDC mainhDC, HDC hdc, float fDeltaTime);
	void PlayExplodeSound();




public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.
	virtual  bool Init(POSITION LTpos, const Pattern& pattern, const Monster_type& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, CBulletList* player_BulletList);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

	void CreateBullet();

};