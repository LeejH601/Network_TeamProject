#pragma once
#include "Monster.h"

class Boss : public CMonster
{
	// CSceneManager 에서 CPlayer의 private 으로 설정된 기본 생성자에 접근하기 위해서 선언 되었습니다...
	friend class CSceneManager;


public:

	Boss();
	Boss(const Boss& player);
	virtual ~Boss();

private:
	class CBulletList* m_bulletList;
	int pattern_count;
	Pattern b_pattern = Pattern::NONE;
	POSITION b_vector = { 0,1 };
	float accum_ceta = 0;
	bool is_reverseCeta = false;



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
	virtual  bool Init(POSITION LTpos, const Monster_type& type, POSITION Vector, int stageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime,class CBulletList* player_BulletList);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

	virtual void CreateBullet(Pattern _pattern);

};
