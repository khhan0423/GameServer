#pragma once


#define _HAS_STD_BYTE	0	//rpcndr.h c++ 17 이상 빌드에러 발생 으로 추가
							//c++17 에서 추가된 std::byte 의 windows.h 의 byte 와의 정의중복 으로 인한 빌드 오류
					

#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "globalMacro.h"
#include "TLSDef.h"