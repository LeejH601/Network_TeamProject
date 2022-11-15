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
private:
	OBJECT_TYPE m_MyType;			// ���� ���� enum class

public:
	// �⺻ ���� �Լ�
	// CObject �� ����ϴ� ��� Ŭ������ �� �����Լ��� ���������� �����Լ�(virtual)�� �����Ѵ�.

	// init ( �̹��� ���� ��� , ȭ�鿡 ����� ������Ʈ ��ġ , ������Ʈ ���� , ������Ʈ ������ , ������Ʈ HP , png ���Ͽ����� ������ , png ���Ͽ����� ��ġ ) 
	virtual bool Init(const WCHAR* imgText, POSITION LTpos, POSITION Vector, _SIZE Size, float HP, POSITION imgSize, POSITION imgLT, PLAYER_TYPE obType);
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

public:
	// �ܺ� ������Ʈ ���� ���� �Լ�
	void SetPos(const POSITION& tPos);
	void SetVector(const POSITION& tVector);
	void SetSize(const _SIZE tSize);

	void SetLife(const bool bLife);
	void SetHP(const float fHP);
	void SetID(const int id);

	virtual bool HandleMessage(const Telegram& telegram);

public:
	bool operator<(const CObject& rhs) {
		return m_iObjN < rhs.GetID();
	}
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
private:
	std::set<CObject*, Compare> ObjectSet;
public:
	bool Init();
	void RegisterObject(CObject* NewObject);
	CObject* GetObjectFromID(int id);
	void RemoveObject(CObject* pObject);
	void RemoveObject(int id);
};