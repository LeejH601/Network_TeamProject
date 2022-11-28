#include "Core.h"
#include "resource.h"
#include "Core/Timer.h"
#include "Object/Object.h"
#include "Scene/SceneManager.h"
#include "Network/NetworkDevice.h"
#include "MessageDispatcher/CMessageDispatcher.h"
#include "Scene/SceneManager.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

HWND my_hDlg;
HINSTANCE my_hInstance;

CCore::CCore()
{
}


CCore::~CCore()
{

	// �̱��� ��ü���� �����մϴ�.
	/*DESTROY_SINGLE(CSoundManager);
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CTimer);*/
	ReleaseDC(m_hWnd, m_hDC);
}

// Game ���� ���� �Լ����Դϴ�. ***

void CCore::Logic()
{
	// ��ŸŸ���� ������ �� ����ϴ�. 
	GET_SINGLE(CTimer)->Update();
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
	// fDeltaTime_update = GET_SINGLE(CTimer)->GetTimer_Update();


	Input(fDeltaTime);			// * �Է�
	Update(fDeltaTime);			// * ������Ʈ
	LateUpdate(fDeltaTime);		// * ������Ʈ ��ó�� 
	Collision(fDeltaTime);		// * �浹 ó��
	Render(fDeltaTime);			// * ���

	if (CNetworkDevice::GetInst()->GetSock())
	{
		CNetworkDevice::GetInst()->SendToNetwork();
		CNetworkDevice::GetInst()->RecvByNetwork();

		CMessageDispatcher::GetInst()->DispatchMessages();
	}
}

void CCore::Input(float fDeltaTime)
{
	// Input�� ó���մϴ�.
	CSceneManager::GetInst()->Input(fDeltaTime);
}
int CCore::Update(float fDeltaTime)
{
	// Update�� ó���մϴ�.
	CSceneManager::GetInst()->Update(fDeltaTime);

	return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
	// LateUpdate�� ó���մϴ�.
	/*CSceneManager::GetInst()->LateUpdate(fDeltaTime);*/

	return 0;
}

void CCore::Collision(float fDeltaTime)
{
	// Collision�� ó���մϴ�.
	/*CSceneManager::GetInst()->Collision(fDeltaTime);*/

}

void CCore::Render(float fDeltaTime)
{
	// Render�� ó���մϴ�.
	CSceneManager::GetInst()->Render(m_hDC, m_hMemDC, fDeltaTime);

}
// Window â ���� �Լ����Դϴ�. ***

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
	// ������â �ڵ�
	m_hWnd = CreateWindowW(TEXT("GALAGA_STARCRAFT"), TEXT("GALAGA_STARCRAFT"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		// ������ â �ڵ� ����⸦ �����Ͽ����ϴ�.
		return FALSE;
	}

	//       ** Ŭ���̾�Ʈ ������ ũ�⸦ ����ϴ�.  **
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	// ������ �����ų �� ������ �޽���
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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

			if (CNetworkDevice::GetInst()->ConnectNetwork(ipv4))
				CCore::GetInst()->SetConnected();

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

	// �ػ� ����
	m_tRS.iW = 600;
	m_tRS.iH = 750;
	bConnected = false;

	Create();

	// ȭ�� DC �� ������ش�.
	m_hDC = GetDC(m_hWnd);
	SetDoubleBufferDC();


	// Ÿ�̸Ӹ� �ʱ�ȭ �մϴ�. 
	if (!CTimer::GetInst()->Init())
		return false;

	// ��Ʈ��ũ ����̽��� �ʱ�ȭ�մϴ�.
	if (!CNetworkDevice::GetInst()->Init())
		return false;

	if (!CObjectManager::GetInst()->Init())
		return false;

	// ��� �����ڸ� �ʱ�ȭ �մϴ�. 
	if (!CSceneManager::GetInst()->Init())
		return false;

	// ���� �Ŵ����� �ʱ�ȭ �մϴ�.
	/*if (!CSoundManager::GetInst()->Init())
		return false;*/

	Telegram testTelegram = Telegram{ 0, 0, (int)MESSAGE_TYPE::Msg_clientReady, CTimer::GetInst()->GetTime(), nullptr };
	CNetworkDevice::GetInst()->AddMessage(testTelegram);

	return true;
}

int CCore::Run()
{
	MSG msg;

	// �⺻ �޽��� �����Դϴ�
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// ������ ����Ÿ���� ���
		else
		{
			// ���ӱ��� logic �� �����˴ϴ�.
			Logic();
		}
	}

	return (int)msg.wParam;
}