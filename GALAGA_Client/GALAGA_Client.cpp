// GALAGA_Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	srand((unsigned int)time(NULL));

	InitializeCriticalSection(&Main_cs);

	// 게임을 초기화 합니다. 
	if (!CCore::GetInst()->Init(hInstance))
	{
		CCore::DestroyInst();
		return 0;
	}

	// 게임 구동을 시작합니다. 
	int iRev = CCore::GetInst()->Run();
	CCore::DestroyInst();

	DeleteCriticalSection(&Main_cs);

	return iRev;

}