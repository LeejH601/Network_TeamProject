#pragma once

#include "Include/Game.h"

class CCore
{


private:
	static bool		m_bLoop;
public:
	DWORD m_hPlayer1;
	DWORD m_hPlayer2;

	void SetPlayerHandle(DWORD threadID, int nPlayer)
	{
		if (!nPlayer)
			m_hPlayer1 = threadID;
		else
			m_hPlayer2 = threadID;
	}
private:
	RESOLUTION	m_tRS;

public:
	void SetEnd()
	{
		m_bLoop = false;

	}

public:
	bool Init();
	int Run();
	
	void Logic();

private:
	
	int Update(float fDeltaTime);					// * 업데이트
	// Update 가 끝나고 충돌전 후처리가 필요한 경우
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌



public:
	RESOLUTION GetResolution()const
	{
		return m_tRS;
	}


private:
	static CCore* m_pInst;

public:
	// static 멤버 함수 : 클래스 네임스페이스만으로 호출 가능
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;

		return m_pInst;

	}
	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}
private:
	CCore();
	~CCore();
};

