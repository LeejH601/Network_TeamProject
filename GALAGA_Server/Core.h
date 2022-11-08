#pragma once

#include "Game.h"

class CCore
{


private:
	static bool		m_bLoop;

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
private:
	void Logic();

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

