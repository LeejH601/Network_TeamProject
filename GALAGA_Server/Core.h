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
	
	int Update(float fDeltaTime);					// * ������Ʈ
	// Update �� ������ �浹�� ��ó���� �ʿ��� ���
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹



public:
	RESOLUTION GetResolution()const
	{
		return m_tRS;
	}


private:
	static CCore* m_pInst;

public:
	// static ��� �Լ� : Ŭ���� ���ӽ����̽������� ȣ�� ����
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

