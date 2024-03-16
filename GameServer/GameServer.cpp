#include "pch.h"
#include "LibTestClass.h"
#include "SocketUtils.h"

int main()
{
	cout << "game server" << endl;
	LibTestClass();
	SocketUtils::Init();
}