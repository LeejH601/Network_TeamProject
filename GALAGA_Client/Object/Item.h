#pragma once
#include "../Include/Game.h"
#include "Object.h"

class CItem : public CObject
{
public:
	// CSceneManager 에서 CPlayer의 private 으로 설정된 기본 생성자에 접근하기 위해서 선언 되었습니다...
	friend class CSceneManager;
public:

	CItem();
	CItem(const CItem& item);
	virtual ~CItem();


private:
	OBJECT_TYPE m_myType;
	bool m_bEnable;

public:

	bool GetEnbale()
	{
		return m_bEnable;
	}
	void SetEnalbeFalse()
	{
		m_bEnable = false;

	}
	OBJECT_TYPE GetType()
	{
		return m_myType;

	}
public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.

	// 생성할 아이템 타입 / 아이템의 생성 위치 지정 / RANDOM 설정 시 아이템 자동 설정 
	virtual bool Init(OBJECT_TYPE itemType, POSITION LTpos);
	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);
	virtual bool HandleMessage(const Telegram& telegram);
};