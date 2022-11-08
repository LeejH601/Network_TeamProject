#pragma once
#include "Game.h"

class CCore
{
private:
	static bool		m_bLoop;
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	RESOLUTION	m_tRS;

	// DoubleBuffer DC 에 관한 변수들 입니다...
	HDC			m_hMemDC;
	HBITMAP		m_hBackBufferBitmap;
	HBITMAP		m_hOldBackBufferBitmap;
public:
	void SetEnd()
	{
		m_bLoop = false;

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

	void Input(float fDeltaTime);					// * 입력
	int Update(float fDeltaTime);					// * 업데이트
	// Update 가 끝나고 충돌전 후처리가 필요한 경우
	int LateUpdate(float fDeltaTime);				// * 업데이트 후처리
	void Collision(float fDeltaTime);				// * 충돌
	void Render(float fDeltaTime);					// * 출력
private:
	//  용도: 창 클래스를 등록합니다.
	ATOM MyRegisterClass();
	//  용도: 윈도우 창 핸들을 받고 영역크기를 지정한 후 출력합니다.
	BOOL Create();
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);
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