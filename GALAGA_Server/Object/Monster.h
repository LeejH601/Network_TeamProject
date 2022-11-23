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
};

class CMonster : public CObject
{
private:
	bool		m_bDie = false;

	CPath m_Path;

public:
	CMonster();
	virtual ~CMonster();

	virtual bool Init(POSITION LTpos, POSITION Vector, _SIZE Size, float HP, PLAYER_TYPE obType);
	virtual	void Update(float fDeltaTime);

	bool GetIsDie()
	{
		return m_bDie;
	}

	virtual bool HandleMessage(const Telegram& telegram);


};