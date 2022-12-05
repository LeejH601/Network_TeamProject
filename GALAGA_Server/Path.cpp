#include "Path.h"

void CPath::Update(float fDeltaTime)
{
	if (m_iIndex < m_points.size() - 4) {
		m_ft += fDeltaTime;
		while (m_ft >= 1.0f) {
			m_ft -= 1.0f;
			m_iIndex++;
			if (!(m_iIndex < m_points.size() - 4)) {
				m_bPathEnd = true;
			}
		}
	}
}

POSITION CPath::GetNextPos()
{
	return CardinalSpline(m_points[m_iIndex], m_points[m_iIndex + 1], m_points[m_iIndex + 2], m_points[m_iIndex + 3], m_ft, m_ftension);
}

void CPath::CalculUniformPos()
{
	float detT = 40.0f;
	std::vector<POSITION> points;
	float length = 0.0f;
	float total_len = 0.0f;
	for (int i = 0; i < m_points.size() - 1 - 3; ++i) {

		//if (length < FLT_EPSILON)
		points.push_back(m_points[i + 1]);
		/*else {
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (length / total_len), m_ftension));
		}*/

		POSITION dist = m_points[i + 2] - m_points[i + 1];
		total_len = sqrt(dist.x * dist.x + dist.y * dist.y);
		length = total_len;

		while (length > detT)
		{
			length -= detT;
			points.push_back(CardinalSpline(m_points[i], m_points[i + 1], m_points[i + 2], m_points[i + 3], (1 - (length / total_len)), m_ftension));
		}
	}

	m_points = points;
}

POSITION CPath::CardinalSpline(POSITION P0, POSITION P1, POSITION P2, POSITION P3, float t, float tension)
{
	POSITION Result;

	float t2 = t * t;
	float t3 = t2 * t;

	float B0 = (-t3 + 2.0 * t2 - t) * (tension);
	float B1 = 1.0 + (tension - 3) * t2 + (2 - tension) * t3;
	float B2 = tension * t + (3 - 2 * tension) * t2 + (tension - 2) * t3;
	float B3 = (t3 - t2) * (tension);

	Result.x = (B0 * P0.x + B1 * P1.x + B2 * P2.x + B3 * P3.x);
	Result.y = (B0 * P0.y + B1 * P1.y + B2 * P2.y + B3 * P3.y);

	return Result;
}
