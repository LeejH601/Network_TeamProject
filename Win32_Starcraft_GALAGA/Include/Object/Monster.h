#pragma once
#include "../Game.h"
#include "Object.h"


enum class Monster_type : int // 몬스터들의 타입
{
	Wraith = 10001,
	Valkyrie = 10002,
	Battlecruiser = 10003,
	Dropship = 10004,
	Vessel = 10005,

	Mutalisk = 20001,
	Devourer = 20002,
	Queen = 20003,
	Scourge = 20004,

	Scout = 30001,
	Corsair = 30002,
	Carrier = 30003,
	Arbiter = 30004,

	BOSS_ONE = 40001,
	BOSS_TWO = 40002,
	BOSS_THREE = 40003
};

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

class CMonster : public  CObject
{
	// CSceneManager 에서 CPlayer의 private 으로 설정된 기본 생성자에 접근하기 위해서 선언 되었습니다...
	friend class CSceneManager;
public:

	CMonster();
	CMonster(const CMonster& player);
	virtual ~CMonster();

protected:
	Pattern		mPattern; // 패턴 분류를 위한 변수
	int			bias = 1;
	float		t_speed = 0.1; // 속도
	bool		d_triger = true; // 계단형 패턴에서 사용하는 방향전환 트리거
	int			count; // 방향 벡터의 업데이트를 위한 카운트
	float		update_count; // 방향 벡터 업데이트를 위한 시간값
	float			t_count;
	float			d_count;
	float		ceta; // 1번의 방향 전환시에 각도를 조절하기 위한 변수
	float		c_det;
	int			fire_delay;
	int			fire_rate;
	float		B_speed = 300.0f;
	MONSTER_STATE m_state = MONSTER_STATE::DONDESTORY;
	float		LastFireTime = NULL;
	float		TracterBimSize = 0;


protected:
	bool		m_bDie = false;
	bool		m_PlayExplodeSound =false;
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
	virtual  bool Init(POSITION LTpos, const Pattern& pattern, const Monster_type& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);

	bool Collision(float fDeltaTime, class CBulletList* player_BulletList);


	MONSTER_STATE GetState() {
		return m_state;
	}

	int GetFireDelay() {
		return fire_delay;
	}

	void CreateBullet(class CBulletList** _bulletList);

};

