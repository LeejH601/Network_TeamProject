#include "..\Common.h"
#include "Core.h"


int main(int argc, char* argv[])
{
	// ������ �ʱ�ȭ �մϴ�. 
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	CCore::GetInst()->Run();

	return 0;
}