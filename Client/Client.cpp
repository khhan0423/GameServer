#include "pch.h"
#include "LibTestClass.h"
#include "SocketUtils.h"

int main()
{
	cout << "client" << endl;
	LibTestClass();
	SocketUtils::Init();
}
