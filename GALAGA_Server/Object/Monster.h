#include "..\Include\Game.h"
#include "Object.h"

class CPath
{
	std::vector<POSITION> m_points;
	float m_ft = 0.0f;
	float m_ftension = 0.5f;

	int m_iIndex = 0;

public:
	void AddPoint(POSITION pos) { m_points.push_back(pos); };
	void SetTension(float tension) { m_ftension = tension; };
	virtual	void Update(float fDeltaTime);

	POSITION GetNextPos();
	void CalculUniformPos();
	POSITION CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension = 0.5);

enum class Pattern {  //
	SIN,
	SIN2,
	SIN3,
	SIN4,
	SIN5,
	SIN6,
	NONE,
	SIN7

};

enum class Monster_type : int
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
private:
	bool m_bDie = false;

	CPath m_Path;
public:
	CMonster();
	virtual ~CMonster();

	virtual bool Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType);
	virtual	void Update(float fDeltaTime);
protected:
	Pattern		mPattern; // ���� �з��� ���� ����
	int			bias = 1;
	float		t_speed = 0.1; // �ӵ�
	bool		d_triger = true; // ����� ���Ͽ��� ����ϴ� ������ȯ Ʈ����
	int			count; // ���� ������ ������Ʈ�� ���� ī��Ʈ
	float		update_count; // ���� ���� ������Ʈ�� ���� �ð���
	float			t_count;
	float			d_count;
	float		ceta; // 1���� ���� ��ȯ�ÿ� ������ �����ϱ� ���� ����
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

	// Test�� ����
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