#include "Core.h"
#include "Core/Timer.h"
#include "Scene/SceneManager.h"
#include "MessageDispatcher/CMessageDispatcher.h"
//#include "Sound/SoundManager.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

CCore::CCore()
{

}


CCore::~CCore()
{
	//DESTROY_SINGLE(CSoundManager);
	//DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CTimer);
}

// Game ���� ���� �Լ����Դϴ�. ***

void CCore::Logic()
{
	// ��ŸŸ���� ������ �� ����ϴ�. 
	GET_SINGLE(CTimer)->Update();
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
	// fDeltaTime_update = GET_SINGLE(CTimer)->GetTimer_Update();

	Update(fDeltaTime);			// * ������Ʈ
	LateUpdate(fDeltaTime);		// * ������Ʈ ��ó�� 
	Collision(fDeltaTime);		// * �浹 ó��

	CMessageDispatcher::GetInst()->DispatchMessages();

}


int CCore::Update(float fDeltaTime)
{
	//std::cout << "Server Update" << std::endl;
	if (CSceneManager::GetInst())
		CSceneManager::GetInst()->Update(fDeltaTime);

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	//std::cout << "Server LateUpdate" << std::endl;

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	//std::cout << "Server Collision" << std::endl;
}





bool CCore::Init()
{
	// �ػ� ����
	m_tRS.iW = 600;
	m_tRS.iH = 750;


	// Ÿ�̸Ӹ� �ʱ�ȭ �մϴ�. 
	if (!CTimer::GetInst()->Init())
		return false;

	// ��� �����ڸ� �ʱ�ȭ �մϴ�. 
	if (!CSceneManager::GetInst()->Init())
		return false;

	// ���� �Ŵ����� �ʱ�ȭ �մϴ�.

	return true;
}

int CCore::Run()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�
	while (m_bLoop)
	{
		// ���ӱ��� logic �� �����˴ϴ�.
		Logic();
	}

	return 1;
}