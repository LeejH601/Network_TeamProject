#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	srand((unsigned int)time(NULL));

	// 게임을 초기화 합니다. 
	if (!CCore::GetInst()->Init(hInstance))
	{
		CCore::DestroyInst();
		return 0;
	}

	// 게임 구동을 시작합니다. 
	int iRev = CCore::GetInst()->Run();
	CCore::DestroyInst();

	return iRev;

}

