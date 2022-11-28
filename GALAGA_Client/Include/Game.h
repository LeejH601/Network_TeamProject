// 전체 헤더파일 관리 목적으로 생성되었습니다.

#pragma once
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

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

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더
#include	<Commctrl.h>

using namespace std;

#include	"Macro.h"
#include	"Types.h"
#include	"Enum.h"

// 사운드 재생 헤더를 선언합니다...
#include	<mmsystem.h>
//#include	<fmod.h>
//#include	<fmod.hpp>
//#include "inc/fmod.h"
//#include "inc/fmod.hpp"
//
//#pragma  comment(lib, "fmodex_vc.lib")

#define BUFSIZE 4096




