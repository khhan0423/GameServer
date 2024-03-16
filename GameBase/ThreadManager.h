#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include "SingletonBase.h"

#define GetThreadManager() ThreadManager::GetInstance()

class ThreadManager : public SingletonBase<ThreadManager>
{
public:
	ThreadManager();
	~ThreadManager();
						//void 형을 반환하는 void 가 인자값인 함수자
						//즉 람다를 받아서 실행.
	void				Launch(function<void(void)> callback);
	void				Join();

	static void			InitTLS();
	static void			ReleaseTLS();

private:
	recursive_mutex		m_lock;
	vector<thread>		m_threadList;
};


