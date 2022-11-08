#include "..\Common.h"
#include "Core.h"


int main(int argc, char* argv[])
{
	// 게임을 초기화 합니다. 
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	CCore::GetInst()->Run();

	return 0;
}