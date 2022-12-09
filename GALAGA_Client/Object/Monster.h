#pragma once
#include "Object.h"

enum class Pattern {  // 패턴 분류용 자료형, 이름엔 별다른 의미가 없는 상태고 추후 교체 예정
	SIN,
	SIN2,
	SIN3,
	SIN4,
	SIN5,
	SIN6,
	NONE,
	SIN7

};

enum class MONSTER_STATE {
	DONDESTORY,
	NOMAL,
	WAIT,
	DESTORY
};

class CMonster : public CObject
{
public:

	CMonster();
	CMonster(const CMonster& player);
protected:
	Pattern		mPattern; // 패턴 분류를 위한 변수
	int			bias = 1;
	float		t_speed = 0.1; // 속도
	bool		d_triger = true; // 계단형 패턴에서 사용하는 방향전환 트리거
	int			count; // 방향 벡터의 업데이트를 위한 카운트
	float		update_count; // 방향 벡터 업데이트를 위한 시간값
	float		t_count;
	float		d_count;
	float		ceta; // 1번의 방향 전환시에 각도를 조절하기 위한 변수
	float		c_det;
	int			fire_delay;
	int			fire_rate;
	float		B_speed = 300.0f;
	float		LastFireTime = NULL;
	float		TracterBimSize = 0;

protected:
	bool		m_bDie = false;
	bool		m_PlayExplodeSound = false;
	CImage		m_Explode_img;

	POINT		m_Explode_img_LT;
	POINT		m_Explode_img_Size;
	int			m_Explode_img_Count = 0;
	bool		m_Explode_img_RenderEnd = false;

public:
	bool GetIsDie()
	{
		return m_bDie;
	}
	POSITION GetMonsterLT()
	{
		return CObject::m_tLTPos;
	}
	POSITION GetMonsterSize()
	{
		return CObject::m_tSize;

	}
	void RenderExplode(HDC mainhDC, HDC hdc, float fDeltaTime);
	void PlayExplodeSound();


public:
	void Run(HDC mainhDC, HDC hdc, float fDeltaTime);


public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.
	virtual  bool Init(POSITION LTpos, const Pattern& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

	int GetFireDelay() {
		return fire_delay;
	}

	virtual bool HandleMessage(const Telegram& msg);
};

