#pragma once


#define _HAS_STD_BYTE	0	//rpcndr.h c++ 17 �̻� ���忡�� �߻� ���� �߰�
							//c++17 ���� �߰��� std::byte �� windows.h �� byte ���� �����ߺ� ���� ���� ���� ����
							

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