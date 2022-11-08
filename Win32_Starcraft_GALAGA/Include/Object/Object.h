#pragma once
#include	"../Game.h"
//**    주의사항   ** 
/*
	->		CObject를 상속하는 class 의 소멸자는 virtual 로 선언해야 합니다..,

	->		Input / Update / LateUpdate / Collision / Render / Init 는 
			obj 클래스를 상속하는 모든 클래스에 공통으로 있어야 할 함수들 입니다.
			이 함수들도 virtual 로 선언하기로 약속합니다...


*/
class CObject
{
private:
	friend class CPlayer;


protected:
	CObject();
	CObject(const CObject& obj); 
	virtual ~CObject();					//  소멸자를 가상함수로 설정합니다..

private:
	CImage*		m_img_Back;				//  이미지
	POSITION	m_img_Size;				//  이미지 ( png )에서 출력할 사이즈 
	POSITION	m_img_LT;				//  이미지 ( png )에서 출력할 위치 


protected:
	POSITION	m_tLTPos;				//  화면에 배치될 Left top 기준 위치
	POSITION	m_tVector;				//  Object 가 움직일 방향
	_SIZE		m_tSize;				//  obj 의 크기 

	bool		m_bLife;				//  obj 의 생사여부
	float		m_fHP;					//  Object 의 HP 

private:
	WCHAR*		m_imgText;


private:
	OBJECT_TYPE m_MyType;			// 종족구분을 위해서 생성된 enum class 를 사용합니다...




public:
	// 기본 구동 함수들 입니다...
	// CObject 를 상속하는 모든 클래스는 이 구동함수를 갖고있으며 가상함수(virtual)로 설정한다.

	// init ( 이미지 파일 경로 , 화면에 출력할 오브젝트 위치 , 오브젝트 방향 , 오브젝트 사이즈 , 오브젝트 HP , png 파일에서의 사이즈 , png 파일에서의 위치 ) 
	virtual  bool Init(const WCHAR* imgText, POSITION LTpos, POSITION Vector, _SIZE Size, float HP, POSITION imgSize, POSITION imgLT, PLAYER_TYPE obType);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

public:

	void Changeimg(const WCHAR* imgText,POSITION imgSize , POSITION imgLT);


	// 외부에서 오브젝트 상태를 확인할 때 사용하는 함수들 입니다...
	POSITION GetPos() const;
	POSITION GetVector() const;
	_SIZE	 GetSize() const;

	bool	 GetLife() const;
	float	 GetHP() const;

public:
	// 외부에서 오브젝트 상태를 설정할 때 사용하는 함수들 입니다...
	void SetPos(const POSITION& tPos);
	void SetVector(const POSITION& tVector);
	void SetSize(const _SIZE tSize);

	void SetLife(const bool bLife);
	void SetHP(const float fHP);


};

