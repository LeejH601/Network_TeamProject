#include "..\Include\Game.h"
#include "Object.h"

class CMonster : public CObject
{
private:
	bool		m_bDie = false;

public:
	CMonster();
	virtual ~CMonster();

	bool GetIsDie()
	{
		return m_bDie;
	}

	virtual bool HandleMessage(const Telegram& telegram);

	POSITION CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension = 0.5);

};