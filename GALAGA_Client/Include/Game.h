// ��ü ������� ���� �������� �����Ǿ����ϴ�.

#pragma once
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include	<unordered_map>
#include	<iostream>
#include	<stdlib.h>
#include	<tchar.h>
#include    "atlImage.h"
#include	<strsafe.h>
#include	<wchar.h>
#include	<algorithm>
#include	<array>
#include	<set>

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���
#include	<Commctrl.h>

using namespace std;

#include	"Macro.h"
#include	"Types.h"
#include	"Enum.h"

// ���� ��� ����� �����մϴ�...
#include	<mmsystem.h>
//#include	<fmod.h>
//#include	<fmod.hpp>
//#include "inc/fmod.h"
//#include "inc/fmod.hpp"
//
//#pragma  comment(lib, "fmodex_vc.lib")

#define BUFSIZE 4096




