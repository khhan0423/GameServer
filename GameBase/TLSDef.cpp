#include "pch.h"
#include "TLSDef.h"
#include "TaskQueue.h"

thread_local unsigned __int32							TLS_ThreadId = 0;
thread_local TaskQueue*									TLS_CurrentTaskQueue = nullptr;

thread_local unsigned __int64							TLS_EndTickCount = 0;