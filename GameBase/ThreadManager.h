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
						//void ���� ��ȯ�ϴ� void �� ���ڰ��� �Լ���
						//�� ���ٸ� �޾Ƽ� ����.
	void				Launch(function<void(void)> callback);
	void				Join();

	static void			InitTLS();
	static void			ReleaseTLS();

private:
	recursive_mutex		m_lock;
	vector<thread>		m_threadList;
};


