#include "pch.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "TaskManager.h"
#include "SocketUtils.h"

ThreadManager* GThreadManager = nullptr;
TaskManager* GTaskManager = nullptr;

class GlobalGameBase
{
public:
	GlobalGameBase()
	{
		GThreadManager = new ThreadManager();
		GTaskManager = new TaskManager();
		SocketUtils::Init();
	}
	~GlobalGameBase()
	{
		delete GThreadManager;
		delete GTaskManager;
		SocketUtils::Clear();
	}
} GGlobalGameBase;