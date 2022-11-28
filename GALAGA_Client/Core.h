#pragma once
#include "Include/Game.h"

extern HWND my_hDlg;

class CCore
{
private:
	static bool		m_bLoop;
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	RESOLUTION	m_tRS;

	// DoubleBuffer DC �� ���� ������ �Դϴ�...
	HDC			m_hMemDC;
	HBITMAP		m_hBackBufferBitmap;
	HBITMAP		m_hOldBackBufferBitmap;
	bool		bConnected;
public:
	void SetEnd()
	{
		m_bLoop = false;

	}
	void proc_tmp()
	{

	}
private:
	void SetDoubleBufferDC()
	{
		m_hMemDC = CreateCompatibleDC(m_hDC);
		m_hBackBufferBitmap = CreateCompatibleBitmap(m_hDC, m_tRS.iW, m_tRS.iH);
		m_hOldBackBufferBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBackBufferBitmap);
	}
public:
	bool Init(HINSTANCE hInst);
	int Run();
private:
	void Logic();

	void Input(float fDeltaTime);					// * �Է�
	int Update(float fDeltaTime);					// * ������Ʈ
	// Update �� ������ �浹�� ��ó���� �ʿ��� ���
	int LateUpdate(float fDeltaTime);				// * ������Ʈ ��ó��
	void Collision(float fDeltaTime);				// * �浹
	void Render(float fDeltaTime);					// * ���
private:
	//  �뵵: â Ŭ������ ����մϴ�.
	ATOM MyRegisterClass();
	//  �뵵: ������ â �ڵ��� �ް� ����ũ�⸦ ������ �� ����մϴ�.
	BOOL Create();
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);

	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	bool IsConnected()
	{
		return bConnected;
	}
	void SetConnected()
	{
		bConnected = true;
	}
private:
	CCore();
	~CCore();
};