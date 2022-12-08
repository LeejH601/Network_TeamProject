#pragma once
#include "..\Include\Game.h"
#include "Monster.h"
#include "BulletList.h"

class CBoss : public CMonster
{
	Pattern m_Pattern;
	float accum_ceta;
	bool is_reverseCeta;
	int pattern_count = 0;

	CBulletList* m_bulletList;

	POSITION b_vector = POSITION(0.f, 1.f);

public:
	CBoss();
	virtual ~CBoss();

	virtual  bool Init(POSITION LTpos, const OBJECT_TYPE& type, POSITION Vector, int stageNum);
	virtual void Update(float fDeltaTime);

	virtual bool HandleMessage(const Telegram& telegram);
	virtual void CreateBullet(Pattern _pattern);

	CBulletList* GetBulletList() { return m_bulletList; };
};

