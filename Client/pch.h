// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

#pragma once

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#include "globalpch.h"

#ifdef _DEBUG
#pragma comment(lib, "GameBase/Debug/GameBase.lib")
#pragma comment(lib, "ProtoBuf/Debug/libprotobufd.lib")
#pragma comment(lib, "OpenXLSX/Debug/OpenXLSXd.lib")

#else
#pragma comment(lib, "GameBase/Release/GameBase.lib")
#pragma comment(lib, "ProtoBuf/Release/libprotobuf.lib")
#pragma comment(lib, "OpenXLSX/Release/OpenXLSX.lib")

#endif