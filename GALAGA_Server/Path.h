#pragma once
#include "Include/Game.h"

class CPath
{
	std::vector<POSITION> m_points;
	float m_ft = 0.0f;
	float m_ftension = 0.5f;

	int m_iIndex = 0;

	bool m_bPathEnd = false;

public:
	void AddPoint(POSITION pos) { m_points.push_back(pos); };
	void SetTension(float tension) { m_ftension = tension; };
	virtual	void Update(float fDeltaTime);

	bool GetPathEnd() { return m_bPathEnd; };

	POSITION GetNextPos();
	void CalculUniformPos();
	POSITION CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension = 0.5);
};
