#pragma once
#include "Object.h"
class CBullet : public CObject
{
public:
    CBullet();
    ~CBullet();

private:
	friend class CPlayer;
	

private:
	float m_fSpeed;	// 총알 스피드
	float m_MaxRange;// 총알 사정거리 

	float m_Range;	
	

private:
	bool m_bEnable; // true 일 경우 총알이 유효합니다... / false 일 경우 삭제 

public:
	
	bool GetEnbale()
	{
		return m_bEnable;
	}
	void SetEnalbeFalse()
	{
		m_bEnable = false;

	}
public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.

	// init 시에 플레이어의 위치와 사이즈 정보를 받습니다. ( 총알 생성 위치에 쓰입니다... )
	virtual  bool Init(POSITION PlayerLT, _SIZE PlayerSize, float Speed);
	virtual  bool Init(POSITION MonsterLT, _SIZE MonsterSize, POSITION BulletVector, float Speed);

	virtual	void Input(float fDeltaTime, class CScene* CurScene);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

};

