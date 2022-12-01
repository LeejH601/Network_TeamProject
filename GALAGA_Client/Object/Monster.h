#pragma once
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
};

enum class MONSTER_PATTERN {
	PAT_STRAIGHT,
	PAT_STAIR_LEFT,
	PAT_STAIR_RIGHT,
	PAT_RING,
	PAT_UTURN,
	END_ENUM,
	PAT_CROSS,
};

class CMonster : public CObject
{
public:

	CMonster();
	CMonster(const CMonster& player);
protected:
	int			bias = 1;
	float		t_speed = 0.1; // �ӵ�
	bool		d_triger = true; // ����� ���Ͽ��� ����ϴ� ������ȯ Ʈ����
	int			count; // ���� ������ ������Ʈ�� ���� ī��Ʈ
	float		update_count; // ���� ���� ������Ʈ�� ���� �ð���
	float		t_count;
	float		d_count;
	float		ceta; // 1���� ���� ��ȯ�ÿ� ������ �����ϱ� ���� ����
	float		c_det;
	int			fire_delay;
	int			fire_rate;
	float		B_speed = 300.0f;
	float		LastFireTime = NULL;
	float		TracterBimSize = 0;

	CPath m_Path;

protected:
	bool		m_bDie = false;
	bool		m_PlayExplodeSound = false;
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
	// �⺻ ���� �Լ��� �Դϴ�...
	// CObject �� ����ϴ� ��� Ŭ������ �� �����Լ��� ���������� �����Լ�(virtual)�� �����Ѵ�.
	virtual  bool Init(POSITION LTpos, const MONSTER_PATTERN& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	void Render(HDC mainhDC, HDC hdc, float fDeltaTime);


	int GetFireDelay() {
		return fire_delay;
	}

	virtual bool HandleMessage(const Telegram& msg);
};

