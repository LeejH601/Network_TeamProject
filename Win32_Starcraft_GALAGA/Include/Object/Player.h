#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:

	// CSceneManager 에서 CPlayer의 private 으로 설정된 기본 생성자에 접근하기 위해서 선언 되었습니다...
	friend class CSceneManager;
	friend class CBullet;
	friend class CBulletList;


public:

	CPlayer();
	CPlayer(const CPlayer& player);
	virtual ~CPlayer();

private:
	bool b_NotDie_Test = false;
	bool m_bHit_TractorBeam = false;

public:
	void SetHitTractorBeam(bool flag)
	{
		m_bHit_TractorBeam = flag;

	}
	bool GetHitTractorBeam()
	{
		return m_bHit_TractorBeam;

	}



private:
	float			m_fSpeed;	// Player 의 속도 입니다..
	OBJECT_TYPE		m_MyType = OBJECT_TYPE::OT_NONE;	// 플레이어의 종족을 구분합니다...


	float		    m_LastFireTime = NULL;
	float			m_fHP_prototype;
	bool			m_bINVINVIBILITY = false;	 // 무적상태
	int				m_INVINVIBILITY_Count = 0;

	CImage			m_Invincibility_img;

private:
	int			m_BulletShotCount;

private:
	int			m_BulletNum = 1;		 // 총알이 나가는 개수 -> 아이템을 먹고 숫작가 늘어나면 늘어난 숫자만큼 발사되는 총알 양이 증가한다. 
private:
	class CBulletList* m_myBulletList;	// 플레이어의 총알을 양뱡향 연결리스트로 관리합니다...

public:
	class CBulletList* GetmyBulletList()
	{
		if (m_myBulletList)
			return m_myBulletList;
		else
			return NULL;

	}



private:
	bool m_bDie = false ;
public:
	bool IsPlayerDie()
	{
		return m_bDie;

	}
	void AddBullet()
	{
		m_BulletNum += 1;
		if (m_BulletNum >= 5)
			m_BulletNum = 5;


	}
	void AddAttack();

	void SetINVINVIBILITY(bool state)
	{
		m_bINVINVIBILITY = state;
	}
	bool GetINVINVIBILITY()
	{
		return m_bINVINVIBILITY;

	}
	void SetHPPrototype()
	{
		CObject::m_fHP = m_fHP_prototype;

	}

public:
	float GetSpeed()
	{
		return m_fSpeed;
	}
	void SetSpeed(float Speed)
	{
		m_fSpeed = Speed;
	}
	float GetMoveDistance(float fDeltaTime)
	{
		return fDeltaTime * m_fSpeed;

	}
	void SetType(int num)
	{
		switch (num)
		{
		case 1:
			m_MyType = OBJECT_TYPE::OT_TERRAN;

			break;
		case 2:
			m_MyType = OBJECT_TYPE::OT_PROTOSS;
			break;
		case  3:
			m_MyType = OBJECT_TYPE::OT_ZERG;

			break;


		default:
			break;
		}
	}
	OBJECT_TYPE GetMyType()
	{
		return m_MyType;

	}



public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.
	virtual  bool Init();

	virtual	void Input(float fDeltaTime,class CScene* CurScene, class CScene* NextScene);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);


	bool Collision(float fDeltaTime, class CBulletList* player_BulletList);
	bool Collision(float fDeltaTime, class CItemList* itemList);
	bool Collision(float fDeltaTime, class CBulletList* player_BulletList, int i);





public:
	void RenderBulletList(HDC mainhDC, HDC hdc, float fDeltaTime);


};

