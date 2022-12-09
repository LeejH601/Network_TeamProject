#include "Core.h"
#include "resource.h"
#include "Core/Timer.h"
#include "Object/Object.h"
#include "Object/Player.h"
#include "Object/Bullet.h"
#include "Scene/SceneManager.h"
#include "Network/NetworkDevice.h"
#include "MessageDispatcher/CMessageDispatcher.h"
#include "Scene/SceneManager.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

HWND my_hDlg;
HINSTANCE my_hInstance;
CRITICAL_SECTION Bullet_CS;

CCore::CCore()
{
}


CCore::~CCore()
{

	// 싱글톤 객체들을 삭제합니다.
	/*DESTROY_SINGLE(CSoundManager);
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CTimer);*/
	ReleaseDC(m_hWnd, m_hDC);
}

// Game 구동 관련 함수들입니다. ***

void CCore::Logic()
{
	// 델타타임을 갱신한 후 얻습니다. 
	GET_SINGLE(CTimer)->Update();
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
	// fDeltaTime_update = GET_SINGLE(CTimer)->GetTimer_Update();


	Input(fDeltaTime);			// * 입력
	Update(fDeltaTime);			// * 업데이트
	LateUpdate(fDeltaTime);		// * 업데이트 후처리 
	Collision(fDeltaTime);		// * 충돌 처리
	Render(fDeltaTime);			// * 출력
}

void CCore::Input(float fDeltaTime)
{
	// Input을 처리합니다.
	CSceneManager::GetInst()->Input(fDeltaTime);
}
int CCore::Update(float fDeltaTime)
{
	// Update를 처리합니다.
	CSceneManager::GetInst()->Update(fDeltaTime);

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	// LateUpdate를 처리합니다.
	CSceneManager::GetInst()->LateUpdate(fDeltaTime);
	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	// Collision을 처리합니다.
	/*CSceneManager::GetInst()->Collision(fDeltaTime);*/

}

void CCore::Render(float fDeltaTime)
{
	// Render를 처리합니다.
	CSceneManager::GetInst()->Render(m_hDC, m_hMemDC, fDeltaTime);

}
void CCore::SendSnapShot()
{
	CPlayer* myPlayer = CSceneManager::GetInst()->GetPlayer();
	if (myPlayer)
	{
		POSITION pos = myPlayer->GetPos();
		Telegram tel_MoveObject;
		tel_MoveObject.Sender = myPlayer->GetID();
		tel_MoveObject.Receiver = myPlayer->GetID();
		tel_MoveObject.Msg = (int)MESSAGE_TYPE::Msg_objectMove;
		tel_MoveObject.DispatchTime = CTimer::GetInst()->GetTime();
		tel_MoveObject.Extrainfo = new char[8];
		memcpy(tel_MoveObject.Extrainfo, &pos, sizeof(POSITION));
		CNetworkDevice::GetInst()->AddMessage(tel_MoveObject);
		delete[] tel_MoveObject.Extrainfo;
	
	}

	if (myPlayer)
	{

		OBJECT_TYPE Type = OBJECT_TYPE::PLAYER_BULLET;
		Telegram telegram;
		telegram.Sender = myPlayer->GetID();
		telegram.Receiver = myPlayer->GetID();
		telegram.Msg = (int)MESSAGE_TYPE::Msg_objectCreate;
		
		if (!(myPlayer->GetmyBulletInfoList())->empty())
		{
			EnterCriticalSection(&Bullet_CS);
			for (const CBulletInfo& bulletInfo : *(myPlayer->GetmyBulletInfoList()))
			{
				telegram.DispatchTime = CTimer::GetInst()->GetTime();
				telegram.Extrainfo = new char[sizeof(OBJECT_TYPE) + sizeof(POSITION)];
				memcpy(telegram.Extrainfo, &Type, sizeof(OBJECT_TYPE));
				memcpy((char*)telegram.Extrainfo + sizeof(OBJECT_TYPE), &(bulletInfo.m_LTPos), sizeof(POSITION));
				CNetworkDevice::GetInst()->AddMessage(telegram);
				delete[] telegram.Extrainfo;

			}
			(myPlayer->GetmyBulletInfoList())->clear();
			LeaveCriticalSection(&Bullet_CS);
		}
	}
}
// Window 창 관련 함수들입니다. ***

ATOM CCore::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(NULL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_GAMEASSORTRAK04PEEKMESSAGEKEY);
	wcex.lpszClassName = TEXT("GALAGA_STARCRAFT");
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(NULL));

	return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
	// 윈도우창 핸들
	m_hWnd = CreateWindowW(TEXT("GALAGA_STARCRAFT"), TEXT("GALAGA_STARCRAFT"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		// 윈도우 창 핸들 만들기를 실패하였습니다.
		return FALSE;
	}

	//       ** 클라이언트 영역의 크기를 맞춥니다.  **
	RECT rc = { 0,0,m_tRS.iW,m_tRS.iH };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	ShowWindow(m_hWnd, SW_SHOW);

	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (!CCore::GetInst()->IsConnected())
		{
			DialogBox(my_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	// 윈도우 종료시킬 때 들어오는 메시지
	case WM_DESTROY:
		m_bLoop = false;
		DeleteCriticalSection(&Bullet_CS);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI ProcessClient(LPVOID arg)
{
	char client_ip[20];
	memcpy(client_ip, arg, 20);

	CNetworkDevice::GetInst()->ConnectNetwork(client_ip);
	CCore::GetInst()->SetConnected();

	Telegram testTelegram = Telegram{ 0, 0, (int)MESSAGE_TYPE::Msg_clientReady, CTimer::GetInst()->GetTime(), nullptr };
	CNetworkDevice::GetInst()->AddMessage(testTelegram);

	while (true)
	{
		float deltaTime = 0.0f;
		while (deltaTime >= 0.02222222f)
		{
			deltaTime += CTimer::GetInst()->GetDeltaTime();
		}

		CCore::GetInst()->SendSnapShot();


		CNetworkDevice::GetInst()->SendToNetwork();
		CNetworkDevice::GetInst()->RecvByNetwork();
		CNetworkDevice::GetInst()->GetTelegram();
		CMessageDispatcher::GetInst()->DispatchMessages();
	}
}


INT_PTR CCore::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		my_hDlg = GetDlgItem(hDlg, IDC_IPADDRESS1);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			DWORD dwAddr;
			SendMessage(my_hDlg, IPM_GETADDRESS, 0, (LPARAM)&dwAddr);
			char ipv4[20];
			StringCchPrintfA(ipv4, _countof(ipv4), "%ld.%ld.%ld.%ld",
				FIRST_IPADDRESS(dwAddr),
				SECOND_IPADDRESS(dwAddr),
				THIRD_IPADDRESS(dwAddr),
				FOURTH_IPADDRESS(dwAddr));

			/*if (CNetworkDevice::GetInst()->ConnectNetwork(ipv4))
				CCore::GetInst()->SetConnected();*/
			HANDLE hThread = CreateThread(NULL, 0, ProcessClient, ipv4, 0, NULL);

			if (hThread == NULL) CloseHandle(hThread);

			DestroyWindow(hDlg);
		}
		return TRUE;
		case IDCANCEL:
			DestroyWindow(hDlg);
			return TRUE;
		}
	}
	return FALSE;
}

bool CCore::Init(HINSTANCE hInst)
{
	this->m_hInst = hInst;
	MyRegisterClass();

	// 해상도 설정
	m_tRS.iW = 600;
	m_tRS.iH = 750;
	bConnected = false;

	Create();

	// 화면 DC 를 만들어준다.
	m_hDC = GetDC(m_hWnd);
	SetDoubleBufferDC();
	InitializeCriticalSection(&Bullet_CS);

	// 타이머를 초기화 합니다. 
	if (!CTimer::GetInst()->Init())
		return false;

	// 네트워크 디바이스를 초기화합니다.
	if (!CNetworkDevice::GetInst()->Init())
		return false;

	if (!CObjectManager::GetInst()->Init())
		return false;

	// 장면 관리자를 초기화 합니다. 
	if (!CSceneManager::GetInst()->Init())
		return false;

	// 사운드 매니저를 초기화 합니다.
	/*if (!CSoundManager::GetInst()->Init())
		return false;*/

	

	return true;
}

int CCore::Run()
{
	MSG msg;

	// 기본 메시지 루프입니다
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// 윈도우 데드타임일 경우
		else
		{
			// 게임구동 logic 이 구현됩니다.
			Logic();
		}
	}

	return (int)msg.wParam;
}