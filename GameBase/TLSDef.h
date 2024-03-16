#pragma once
#include "TaskQueue.h"

extern thread_local unsigned __int32							TLS_ThreadId;
extern thread_local TaskQueue*									TLS_CurrentTaskQueue;

extern thread_local unsigned __int64							TLS_EndTickCount;

