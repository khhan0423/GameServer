#pragma once
//rpcndr.h c++ 17 이상 빌드에러 발생
//c++17 에서 추가된 std::byte 의 windows.h 의 byte 와의 정의중복 으로 인한 빌드 오류
#define _HAS_STD_BYTE	0

#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "globalMacro.h"
#include "ProtocolResultEnum.h"
#include "TLSDef.h"
#include "LogBase.h"
