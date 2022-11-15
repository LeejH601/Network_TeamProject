#pragma once
#include "../Include/Game.h"

class CObject
{
public:
	static int m_iObjN;
public:
	CObject();
	CObject(const CObject& obj);
	virtual ~CObject();					//  소멸자를 가상함수로 설정합니다..
protected:
	int m_iObjID;

	POSITION	m_tLTPos;				//  화면에 배치될 Left top 기준 위치
	POSITION	m_tVector;				//  Object 가 움직일 방향
	_SIZE		m_tSize;				//  obj 의 크기 

	bool		m_bLife;				//  obj 의 생사여부
	float		m_fHP;					//  Object 의 HP 
private:
	OBJECT_TYPE m_MyType;			// 종족 구분 enum class

public:
	// 기본 구동 함수
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.

	// init ( 이미지 파일 경로 , 화면에 출력할 오브젝트 위치 , 오브젝트 방향 , 오브젝트 사이즈 , 오브젝트 HP , png 파일에서의 사이즈 , png 파일에서의 위치 ) 
	virtual bool Init(const WCHAR* imgText, POSITION LTpos, POSITION Vector, _SIZE Size, float HP, POSITION imgSize, POSITION imgLT, PLAYER_TYPE obType);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);


public:
	// 외부 오브젝트 상태 확인 함수
	POSITION GetPos() const;
	POSITION GetVector() const;
	_SIZE	 GetSize() const;

	bool	 GetLife() const;
	float	 GetHP() const;
	int		 GetID() const;

public:
	// 외부 오브젝트 상태 설정 함수
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
	// 싱글톤 선언
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