#include "..\Include\Game.h"
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
	bool		m_PlayExplodeSound = false;
	CImage		m_Explode_img;

	POINT		m_Explode_img_LT;
	POINT		m_Explode_img_Size;
	int			m_Explode_img_Count = 0;
	bool		m_Explode_img_RenderEnd = false;

	// Test용 변수
	bool		m_bBullet = true;
public:

	bool GetIsDie()
	{
		return m_bDie;
	}

	virtual bool HandleMessage(const Telegram& telegram);

	void CreateBullet(class CBulletList** _bulletList);


	virtual  bool Init(POSITION LTpos, const Pattern& pattern, const Monster_type& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	void	Msg_Create(Monster_type TYPE, POSITION POS);
	void	Msg_Move(POSITION POS);


	MONSTER_STATE GetState() {
		return m_state;
	}

	int GetFireDelay() {
		return fire_delay;
	}
};