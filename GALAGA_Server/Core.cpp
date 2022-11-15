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

// Game 구동 관련 함수들입니다. ***

void CCore::Logic()
{
	// 델타타임을 갱신한 후 얻습니다. 
	GET_SINGLE(CTimer)->Update();
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
	// fDeltaTime_update = GET_SINGLE(CTimer)->GetTimer_Update();

	Update(fDeltaTime);			// * 업데이트
	LateUpdate(fDeltaTime);		// * 업데이트 후처리 
	Collision(fDeltaTime);		// * 충돌 처리

	CMessageDispatcher::GetInst()->DispatchMessages();

}


int CCore::Update(float fDeltaTime)
{
	std::cout << "Server Update" << std::endl;

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	std::cout << "Server LateUpdate" << std::endl;

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	std::cout << "Server Collision" << std::endl;
}





bool CCore::Init()
{
	// 해상도 설정
	m_tRS.iW = 600;
	m_tRS.iH = 750;


	// 타이머를 초기화 합니다. 
	if (!CTimer::GetInst()->Init())
		return false;

	// 장면 관리자를 초기화 합니다. 
	if (!CSceneManager::GetInst()->Init())
		return false;

	// 사운드 매니저를 초기화 합니다.

	return true;
}

int CCore::Run()
{
	MSG msg;

	// 기본 메시지 루프입니다
	while (m_bLoop)
	{
		// 게임구동 logic 이 구현됩니다.
		Logic();
	}

	return 1;
}