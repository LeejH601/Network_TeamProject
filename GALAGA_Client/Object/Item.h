#pragma once
#include "../Include/Game.h"
#include "Object.h"

class CItem : public CObject
{
public:
	// CSceneManager ���� CPlayer�� private ���� ������ �⺻ �����ڿ� �����ϱ� ���ؼ� ���� �Ǿ����ϴ�...
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
	// �⺻ ���� �Լ��� �Դϴ�...
	// CObject �� ����ϴ� ��� Ŭ������ �� �����Լ��� ���������� �����Լ�(virtual)�� �����Ѵ�.

	// ������ ������ Ÿ�� / �������� ���� ��ġ ���� / RANDOM ���� �� ������ �ڵ� ���� 
	virtual bool Init(OBJECT_TYPE itemType, POSITION LTpos);
	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);
	virtual bool HandleMessage(const Telegram& telegram);
};