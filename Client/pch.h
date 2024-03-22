// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include "globalpch.h"

#ifdef _DEBUG
#pragma comment(lib, "GameBase/Debug/GameBase.lib")
#pragma comment(lib, "ProtoBuf/Debug/libprotobufd.lib")
#pragma comment(lib, "libboost_nowide-vc143-mt-gd-x64-1_84.lib")
#pragma comment(lib, "OpenXLSX/Debug/OpenXLSXd.lib")

#else
#pragma comment(lib, "GameBase/Release/GameBase.lib")
#pragma comment(lib, "ProtoBuf/Release/libprotobuf.lib")
#pragma comment(lib, "libboost_nowide-vc143-mt-x64-1_84.lib")
#pragma comment(lib, "OpenXLSX/Release/OpenXLSX.lib")

#endif

