#include "pch.h"
#include "ThreadManager.h"
#include "TaskManager.h"
#include "GlobalGameBase.h"

ThreadManager::ThreadManager()
{
	DebugLog("[%s]", __FUNCTION__);
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	DebugLog("[%s]", __FUNCTION__);
	ReleaseTLS();
	Join();
}

void ThreadManager::Launch(std::function<void(void)> callback)
{
	DebugLog("[%s]", __FUNCTION__);
	{
		std::lock_guard<std::recursive_mutex> lock(m_lock);
		m_threadList.push_back(std::thread([=]()
			{
				InitTLS();
				callback();
				ReleaseTLS();
			}));
	}
}

void ThreadManager::Join()
{
	DebugLog("[%s]", __FUNCTION__);
	for (std::thread& _thread : m_threadList)
	{
		if (_thread.joinable())
			_thread.join();
	}
	m_threadList.clear();
}

void ThreadManager::Run()
{
	
	while (true)
	{
		unsigned __int64 _now = ::GetTickCount64();
		if (_now > TLS_EndTickCount)
			break;


		std::shared_ptr<TaskQueue> _taskLine = GTaskManager->Pop();

		if (_taskLine == nullptr)
			break;

		_taskLine->Run();
		
		std::this_thread::yield();
	}
}

void ThreadManager::InitTLS()
{
	//static 이라 프로세스 구동 시
	//값 1로 세팅되며, 런타임에 static Tatomic<uint32> SThreadId = 1; 구문은 패스된다.
	static std::atomic<unsigned __int32> SThreadId = 1;
	TLS_ThreadId = SThreadId.fetch_add(1);
	
	DebugLog("[%s]", __FUNCTION__);
}

void ThreadManager::ReleaseTLS()
{
	DebugLog("[%s]", __FUNCTION__);
}
