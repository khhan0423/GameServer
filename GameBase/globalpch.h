#pragma once

#include "globalMacro.h"
#include "TLSDef.h"

#include <windows.h>
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

static void fnGameBase()
{
	cout << "print any thing" << endl;
}