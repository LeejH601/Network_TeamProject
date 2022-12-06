#pragma once
#include "../Include/Game.h"

class CObject
{
public:
	static int m_iObjN;
public:
	CObject();
	CObject(const CObject& obj);
	virtual ~CObject();					//  �Ҹ��ڸ� �����Լ��� �����մϴ�..
protected:
	int m_iObjID;

	POSITION	m_tLTPos;				//  ȭ�鿡 ��ġ�� Left top ���� ��ġ
	POSITION	m_tVector;				//  Object �� ������ ����
	_SIZE		m_tSize;				//  obj �� ũ�� 

	bool		m_bLife;				//  obj �� ���翩��
	float		m_fHP;					//  Object �� HP
	float		m_fStateTerm;
protected:
	TRIBE_TYPE m_MyType;			// ���� ���� enum class
	OBJECT_TYPE m_eObjType;
	OBJECT_STATE m_eObjState = OBJECT_STATE::IDLE;
public:
	// �⺻ ���� �Լ�
	// CObject �� ����ϴ� ��� Ŭ������ �� �����Լ��� ���������� �����Լ�(virtual)�� �����Ѵ�.

	// init ( ȭ�鿡 ����� ������Ʈ ��ġ , ������Ʈ ���� , ������Ʈ ������ , ������Ʈ HP , PLAYER or MONSTER) 
	virtual bool Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);


public:
	// �ܺ� ������Ʈ ���� Ȯ�� �Լ�
	POSITION GetPos() const;
	POSITION GetVector() const;
	_SIZE	 GetSize() const;

	bool	 GetLife() const;
	float	 GetHP() const;
	int		 GetID() const;
	OBJECT_TYPE GetObjType() const { return m_eObjType; } ;
	OBJECT_STATE GetObjectState() const { return m_eObjState; };

public:
	// �ܺ� ������Ʈ ���� ���� �Լ�
	void SetPos(const POSITION& tPos);
	void SetVector(const POSITION& tVector);
	void SetSize(const _SIZE tSize);
	void SetState(const OBJECT_STATE state) { m_eObjState = state; };

	void SetLife(const bool bLife);
	void SetHP(const float fHP);
	void SetID(const int id);
	void SetObjType(const OBJECT_TYPE type) { m_eObjType = type; };

	virtual bool HandleMessage(const Telegram& telegram);
};

class Compare {
public:
	bool operator()(const CObject* lhs, const CObject* rhs) const {
		return lhs->GetID() < rhs->GetID();
	}
};

class CObjectManager
{
public:
	// �̱��� ����
	DECLARE_SINGLE(CObjectManager);
public:
	std::set<CObject*, Compare> ObjectSet;
public:
	bool Init();
	void RegisterObject(CObject* NewObject);
	CObject* GetObjectFromID(int id);
	void RemoveObject(CObject* pObject);
	void RemoveObject(int id);
};