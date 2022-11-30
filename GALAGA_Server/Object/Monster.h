#pragma once
#include "..\Include\Game.h"
#include "..\Include\Enum.h"
#include "Object.h"
#include "..\Path.h"

class CMonster : public CObject
{
private:
	bool m_bDie = false;

	CPath m_Path;
public:
	CMonster();
	virtual ~CMonster();

	virtual bool Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType);
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
	float		fire_delay = 500.0f;
	float		fire_rate = 500.0f;
	float		B_speed = 300.0f;
	float		LastFireTime = NULL;
	float		TracterBimSize = 0;


protected:
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


	virtual  bool Init(POSITION LTpos, const MONSTER_PATTERN& pattern, const OBJECT_TYPE& type, POSITION Vector, int StageNum);

	virtual	void Input(float fDeltaTime);
	virtual	void Update(float fDeltaTime);
	virtual	void LateUpdate(float fDeltaTime);
	virtual	bool Collision(float fDeltaTime, POSITION ObjectLT, POSITION ObjectSize);
	void	Msg_Create(OBJECT_TYPE TYPE, POSITION POS);
	void	Msg_Move(POSITION POS);



	float GetFireDelay() {
		return fire_delay;
	}
};