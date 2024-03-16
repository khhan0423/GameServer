#include "pch.h"
#include "ThreadManager.h"

ThreadManager::ThreadManager()
{
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		m_threadList.push_back(thread([=]()
			{
				InitTLS();
				callback();
				ReleaseTLS();
			}));
	}
}

void ThreadManager::Join()
{
	for (thread& _thread : m_threadList)
	{
		if (_thread.joinable())
			_thread.join();
	}
	m_threadList.clear();
}

void ThreadManager::InitTLS()
{
	//static �̶� ���μ��� ���� ��
	//�� 1�� ���õǸ�, ��Ÿ�ӿ� static Tatomic<uint32> SThreadId = 1; ������ �н��ȴ�.
	static atomic<unsigned __int32> SThreadId = 1;
	TLS_ThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::ReleaseTLS()
{

}
