// ��ü ������� ���� �������� �����Ǿ����ϴ�.

#pragma once
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include	<list>
#include	<vector>
#include	<unordered_map>
#include	<iostream>
#include	<stdlib.h>
#include	<tchar.h>
#include    "atlImage.h"
#include	<strsafe.h>
#include	<string.h>
#include	<wchar.h>
#include	<set>
#include	<array>

#include <WinSock2.h>
#include <ws2tcpip.h>

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


extern CRITICAL_SECTION cs;


